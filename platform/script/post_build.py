import os
import shutil
import threading
import time
from os.path import join, expanduser

import json
import subprocess
import sys
# ==========================================================
# ตรวจสอบ ~/.beearduino/config.json ถ้าไม่มี ให้รัน setup.py
# ==========================================================
user_path = expanduser("~")
bee_dir = join(user_path, ".beearduino")
config_file = join(bee_dir, "config.json")

project_dir = os.getcwd()
setup_script = join(project_dir, "platform", "setup", "setup.py")

def run_setup():
    if os.path.isfile(setup_script):
        print(f"[INFO] Running setup: {setup_script}")
        try:
            subprocess.run([sys.executable, setup_script], check=True)
        except subprocess.CalledProcessError as e:
            print(f"[ERROR] setup.py exited with error: {e}")
        except Exception as e:
            print(f"[ERROR] Failed to run setup.py: {e}")
    else:
        print(f"[ERROR] setup.py not found at: {setup_script}")

if not os.path.isfile(config_file):
    print(f"[INFO] config.json not found — running setup...")
    run_setup()
else:
    print(f"[INFO] config.json found at: {config_file}")
    try:
        with open(config_file, "r", encoding="utf-8") as f:
            config = json.load(f)
        project_home = config.get("project_home", "")

        if os.path.normpath(project_home) != os.path.normpath(project_dir):
            print(f"[WARN] project_home mismatch. Updating config.json...")
            config["project_home"] = project_dir
            with open(config_file, "w", encoding="utf-8") as f:
                json.dump(config, f, indent=2, ensure_ascii=False)
            print(f"[INFO] Updated project_home → {project_dir}")
        else:
            print(f"[INFO] project_home matches current project.")
    except Exception as e:
        print(f"[ERROR] Failed to read or update config.json: {e}")


Import("env")

build_dir = env.subst("$BUILD_DIR")
project_dir = env['PROJECT_DIR']
user_dir = env.get("USER_DIR", expanduser("~"))
toolchain_bin = join(user_dir, ".beearduino", "toolchain", "bin")

dlls = ["SDL2.dll", "libgcc_s_seh-1.dll", "libstdc++-6.dll", "libwinpthread-1.dll"]

dist_dir = join(project_dir, "dist")
os.makedirs(dist_dir, exist_ok=True)

project_name = env.GetProjectOption("project_name") or env['PIOENV']
exe_dst_path = join(dist_dir, f"{project_name}.exe")
lock_file = join(dist_dir, ".exe_copy_lock")

# ----------------------------
# Copy DLLs ทันที
# ----------------------------
for dll in dlls:
    src = join(toolchain_bin, dll)
    dst = join(dist_dir, dll)
    if os.path.exists(src):
        if not os.path.exists(dst) or os.path.getmtime(src) > os.path.getmtime(dst):
            shutil.copy2(src, dst)
            print(f"[POST BUILD] DLL copied: {dll}")
    else:
        print(f"[POST BUILD] Warning: DLL not found: {src}")

# ----------------------------
# Thread สำหรับ copy .exe หลัง build
# ----------------------------
def copy_exe_thread():
    # เขียน lock file
    with open(lock_file, "w") as f:
        f.write("lock")

    exe_src_path = None

    # รอจนเจอไฟล์ .exe ขนาด > 0
    while exe_src_path is None:
        for root, dirs, files in os.walk(build_dir):
            for file in files:
                if file.lower().endswith(".exe"):
                    candidate = join(root, file)
                    if os.path.getsize(candidate) > 0:  # ตรวจสอบไฟล์มีเนื้อหา
                        exe_src_path = candidate
                        break
            if exe_src_path:
                break
        if exe_src_path is None:
            time.sleep(0.5)

    # copy ไป dist
    shutil.copy2(exe_src_path, exe_dst_path)
    print(f"[POST BUILD] .exe copied: {exe_dst_path}")

    # ลบ lock file หลัง copy เสร็จ
    if os.path.exists(lock_file):
        os.remove(lock_file)

# ----------------------------
# kill thread เดิมถ้ามี
# ----------------------------
try:
    if os.path.exists(lock_file):
        os.remove(lock_file)
except:
    pass

# สร้าง thread ใหม่
thread = threading.Thread(target=copy_exe_thread, daemon=True)
thread.start()
