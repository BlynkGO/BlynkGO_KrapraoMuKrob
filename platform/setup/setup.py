import os
import json
import zipfile
import shutil
import subprocess
import hashlib
import psutil
from pathlib import Path

# ==========================================================
# CONFIG
# ==========================================================
JSON_FILE = "packages.json"  # ไฟล์ JSON
ROOT_DIR = Path.home() / ".beearduino"
DOWNLOAD_DIR = ROOT_DIR / "download"
ARIA2C_EXE = "aria2c.exe"  # ต้องอยู่ใน PATH หรือ full path

# ==========================================================
# FUNCTIONS
# ==========================================================

def ensure_directories():
    """สร้างโฟลเดอร์หลักและ download ถ้ายังไม่มี"""
    ROOT_DIR.mkdir(exist_ok=True)
    DOWNLOAD_DIR.mkdir(exist_ok=True)
    print(f"[✓] ตรวจสอบโฟลเดอร์เรียบร้อย: {ROOT_DIR}")

def get_toolchain_info():
    """อ่าน URL, filename, size และ checksum จาก JSON"""
    with open(JSON_FILE, "r", encoding="utf-8") as f:
        data = json.load(f)

    tool = data["packages"][0]["tools"][0]
    system = tool["systems"][0]
    url = system["url"]
    filename = system["archiveFileName"]
    size = system.get("size")
    checksum = system.get("checksum")  # เช่น SHA-256:xxxxxxxx
    return url, filename, size, checksum

def sha256_checksum(file_path):
    """คำนวณ SHA-256 ของไฟล์"""
    h = hashlib.sha256()
    with open(file_path, "rb") as f:
        for chunk in iter(lambda: f.read(8192), b""):
            h.update(chunk)
    return h.hexdigest()

def download_toolchain(url, filename, expected_size=None, checksum=None):
    """ดาวน์โหลด zip ด้วย aria2c ถ้ายังไม่มีหรือไม่ตรง"""
    dest_path = DOWNLOAD_DIR / filename

    # ตรวจสอบไฟล์เดิม
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
        "-x", "4",           # concurrent connections
        "-s", "4",
        "-c",                # resume
        "-o", str(dest_path.name),
        url
    ]
    subprocess.run(cmd, cwd=str(DOWNLOAD_DIR), check=True)
    print(f"[✓] ดาวน์โหลดเสร็จสิ้น: {dest_path}")

    # ตรวจสอบอีกครั้ง
    if expected_size and dest_path.stat().st_size != expected_size:
        raise ValueError(f"ดาวน์โหลดไฟล์ {filename} ขนาดไม่ตรง: {dest_path.stat().st_size} != {expected_size}")
    if checksum and checksum.startswith("SHA-256:"):
        sha256 = checksum.split(":")[1].strip()
        file_sha256 = sha256_checksum(dest_path)
        if file_sha256 != sha256:
            raise ValueError(f"SHA-256 ของไฟล์ไม่ตรง: {file_sha256} != {sha256}")

    return dest_path

def remove_old_toolchain():
    """ลบไฟล์/โฟลเดอร์ toolchain เดิมใน .beearduino"""
    for item in ROOT_DIR.iterdir():
        if item.is_dir() and item.name != "download":
            print(f"[x] ลบโฟลเดอร์เก่า: {item}")
            shutil.rmtree(item)
        elif item.is_file():
            print(f"[x] ลบไฟล์เก่า: {item}")
            item.unlink()

def get_uncompressed_size(zip_path):
    """คืนค่าขนาดทั้งหมดของไฟล์ใน zip (หน่วยเป็น bytes)"""
    total = 0
    with zipfile.ZipFile(zip_path, "r") as z:
        for info in z.infolist():
            total += info.file_size
    return total

def check_free_space(path, required_bytes):
    """ตรวจสอบว่าพื้นที่ว่างพอไหม"""
    usage = psutil.disk_usage(path)
    free_bytes = usage.free
    if free_bytes < required_bytes:
        raise OSError(
            f"[✗] พื้นที่ไม่เพียงพอ ต้องการ {required_bytes/1e9:.2f} GB "
            f"แต่เหลือ {free_bytes/1e9:.2f} GB"
        )
    print(f"[✓] พื้นที่เพียงพอ: ต้องการ {required_bytes/1e9:.2f} GB เหลือ {free_bytes/1e9:.2f} GB")

def extract_toolchain(zip_path):
    """แตกไฟล์ zip ไปที่ ROOT_DIR"""
    print(f"[⇪] กำลังตรวจสอบพื้นที่ ...")
    uncompressed_size = get_uncompressed_size(zip_path)
    check_free_space(ROOT_DIR, uncompressed_size * 1.1)  # เผื่ออีก 10%

    print(f"[⇪] กำลังแตกไฟล์ {zip_path} ...")
    with zipfile.ZipFile(zip_path, "r") as zip_ref:
        zip_ref.extractall(ROOT_DIR)
    print(f"[✓] แตกไฟล์เสร็จสิ้นที่ {ROOT_DIR}")

# ==========================================================
# MAIN
# ==========================================================

def main():
    ensure_directories()
    url, filename, expected_size, checksum = get_toolchain_info()
    zip_path = download_toolchain(url, filename, expected_size, checksum)
    remove_old_toolchain()
    extract_toolchain(zip_path)
    print("[✓] ทุกขั้นตอนเสร็จสมบูรณ์!")

if __name__ == "__main__":
    main()
