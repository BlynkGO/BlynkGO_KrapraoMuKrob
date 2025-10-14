import os
import shutil
from os.path import join, expanduser

Import("env")

# --- Paths ---
build_dir = env.subst("$BUILD_DIR")
project_dir = env['PROJECT_DIR']

# ใช้ USER_DIR ของ PlatformIO
user_dir = env.get("USER_DIR", expanduser("~"))
toolchain_bin = join(user_dir, ".beearduino", "toolchain", "bin")

# DLLs list
dlls = ["SDL2.dll", "libgcc_s_seh-1.dll", "libstdc++-6.dll", "libwinpthread-1.dll"]

# dist folder
dist_dir = join(project_dir, "dist")
os.makedirs(dist_dir, exist_ok=True)

# --- project_name ---
project_name = env.GetProjectOption("project_name") or env['PIOENV']
print(f"[POST BUILD] Using project_name: {project_name}")

# --- Copy exe ---
exe_found = False
for root, dirs, files in os.walk(build_dir):
    for file in files:
        if file.lower().endswith(".exe"):
            exe_found = True
            src = join(root, file)
            dst_name = f"{project_name}.exe"
            dst = join(dist_dir, dst_name)
            print(f"[POST BUILD] Copy {file} -> {dst_name}")
            shutil.copy2(src, dst)  # จะเขียนทับไฟล์เดิมถ้ามี

if not exe_found:
    print(f"[POST BUILD] Warning: No .exe found in build dir: {build_dir}")

# --- Copy DLLs ---
for dll in dlls:
    src = join(toolchain_bin, dll)
    if os.path.exists(src):
        dst = join(dist_dir, dll)
        print(f"[POST BUILD] Copy {dll} to dist")
        shutil.copy2(src, dst)  # จะเขียนทับไฟล์เดิมถ้ามี
    else:
        print(f"[POST BUILD] Warning: DLL not found: {dll}")
        print(f"  Checked path: {src}")
