
# v0.9.2
import os
import sys
import json
import shutil
import subprocess
import hashlib
from pathlib import Path

# -------------------------------
# ตรวจสอบว่า psutil
try:
    import psutil
except ImportError:
    print("psutil not found. Installing automatically...")
    subprocess.check_call([sys.executable, "-m", "pip", "install", "psutil"])
    import psutil
# -------------------------------

# ==========================================================
# CONFIG
# ==========================================================
JSON_FILE = "packages.json"  # ไฟล์ JSON
ROOT_DIR = Path.home() / ".beearduino"
DOWNLOAD_DIR = ROOT_DIR / "download"
ARIA2C_EXE = "aria2c.exe"  # ต้องอยู่ใน PATH หรือ full path
WINRAR_EXE = r"C:\Program Files\WinRAR\WinRAR.exe"  # path ของ WinRAR

# ==========================================================
# FUNCTIONS
# ==========================================================

def ensure_directories():
    ROOT_DIR.mkdir(exist_ok=True)
    DOWNLOAD_DIR.mkdir(exist_ok=True)
    print(f"[✓] ตรวจสอบโฟลเดอร์เรียบร้อย: {ROOT_DIR}")

def sha256_checksum(file_path):
    h = hashlib.sha256()
    with open(file_path, "rb") as f:
        for chunk in iter(lambda: f.read(8192), b""):
            h.update(chunk)
    return h.hexdigest()

def download_tool(url, filename, expected_size=None, checksum=None):
    dest_path = DOWNLOAD_DIR / filename

    if dest_path.exists():
        size_ok = (expected_size is None) or (dest_path.stat().st_size == expected_size)
        checksum_ok = True
        if checksum and checksum.startswith("SHA-256:"):
            sha256 = checksum.split(":")[1].strip()
            file_sha256 = sha256_checksum(dest_path)
            checksum_ok = (file_sha256 == sha256)

        if size_ok and checksum_ok:
            print(f"[✓] พบไฟล์ {filename} อยู่แล้วและถูกต้อง — ข้ามการดาวน์โหลด")
            return dest_path
        else:
            print(f"[!] ไฟล์ {filename} ไม่ตรงขนาดหรือ checksum — ลบแล้วดาวน์โหลดใหม่")
            dest_path.unlink()

    print(f"[↓] กำลังดาวน์โหลด {filename} ด้วย aria2c ...")
    cmd = [
        ARIA2C_EXE,
        "-x", "4",
        "-s", "4",
        "-c",
        "-o", str(dest_path.name),
        url
    ]
    subprocess.run(cmd, cwd=str(DOWNLOAD_DIR), check=True)
    print(f"[✓] ดาวน์โหลดเสร็จสิ้น: {dest_path}")
    return dest_path

def check_free_space(path, required_bytes):
    usage = psutil.disk_usage(str(path))
    free_bytes = usage.free
    if free_bytes < required_bytes:
        raise OSError(
            f"[✗] พื้นที่ไม่เพียงพอ ต้องการ {required_bytes/1e9:.2f} GB "
            f"แต่เหลือ {free_bytes/1e9:.2f} GB"
        )
    print(f"[✓] พื้นที่เพียงพอ: ต้องการ {required_bytes/1e9:.2f} GB เหลือ {free_bytes/1e9:.2f} GB")

def get_uncompressed_size(zip_path):
    """ประเมินขนาด uncompressed โดยประมาณ"""
    # ถ้าอยากได้ exact อาจใช้ zipfile แต่ WinRAR จะตรวจสอบอีกที
    return zip_path.stat().st_size * 3  # เผื่อไว้ 3 เท่า

def extract_zip(zip_path, target_dir):
    """แตกไฟล์ด้วย WinRAR"""
    target_dir.mkdir(exist_ok=True)
    print(f"[⇪] กำลังตรวจสอบพื้นที่ ...")
    estimated_size = get_uncompressed_size(zip_path)
    check_free_space(target_dir, estimated_size)
    print(f"[⇪] กำลังแตกไฟล์ {zip_path} ไปที่ {target_dir} ...")
    cmd = [WINRAR_EXE, "x", "-ibck", "-y", str(zip_path), str(target_dir)]
    subprocess.run(cmd, check=True)
    print(f"[✓] แตกไฟล์เสร็จสิ้นที่ {target_dir}")

def remove_old_dir(path):
    if path.exists():
        print(f"[x] ลบโฟลเดอร์เก่า: {path}")
        shutil.rmtree(path)

def get_tool_info(name):
    with open(JSON_FILE, "r", encoding="utf-8") as f:
        data = json.load(f)
    for tool in data["packages"][0]["tools"]:
        if tool["name"] == name:
            system = tool["systems"][0]
            return system["url"], system["archiveFileName"], system.get("size"), system.get("checksum")
    return None, None, None, None

# ==========================================================
# MAIN
# ==========================================================

def main():
    ensure_directories()

    # ----------------------------
    # Toolchain
    # ----------------------------
    print("\n=== กำลังจัดการ Toolchain ===")
    url, filename, size, checksum = get_tool_info("BeeArduino_Toolchain")
    zip_path = download_tool(url, filename, size, checksum)
    remove_old_dir(ROOT_DIR / "toolchain")
    extract_zip(zip_path, ROOT_DIR)
    print("[✓] Toolchain เสร็จเรียบร้อย!")

    # ----------------------------
    # BlynkGOv5_tools
    # ----------------------------
    print("\n=== กำลังจัดการ BlynkGOv5_tools ===")
    url, filename, size, checksum = get_tool_info("BlynkGOv5_tools")
    zip_path = download_tool(url, filename, size, checksum)
    remove_old_dir(ROOT_DIR / "tools")
    extract_zip(zip_path, ROOT_DIR)
    print("[✓] BlynkGOv5_tools เสร็จเรียบร้อย!")

    # ----------------------------
    # Copy *.cmd ไป WindowsApps
    # ----------------------------
    tools_dir = ROOT_DIR / "tools"
    windows_apps_dir = Path(os.environ["LOCALAPPDATA"]) / "Microsoft" / "WindowsApps"

    if tools_dir.exists():
        for cmd_file in tools_dir.glob("*.cmd"):
            dest_file = windows_apps_dir / cmd_file.name
            try:
                shutil.copy(cmd_file, dest_file)
                print(f"[✓] คัดลอก {cmd_file.name} ไป {dest_file}")
            except Exception as e:
                print(f"[!] ไม่สามารถคัดลอก {cmd_file.name}: {e}")

    print("\n[✓] ทุกขั้นตอนเสร็จสมบูรณ์!")

if __name__ == "__main__":
    main()
