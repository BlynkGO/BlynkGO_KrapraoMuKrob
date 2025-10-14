import os
import json
from os.path import join, expanduser
from SCons.Script import Import

Import("env")

# ==========================================================
# ตั้งค่า USER_DIR และ toolchain
# ==========================================================
user_path = expanduser("~")  # path ไปยัง home ของ user
env["USER_DIR"] = user_path  # ให้ PlatformIO ใช้ $USER_DIR ได้ใน build_flags

toolchain_root = join(user_path, ".beearduino", "toolchain")
toolchain_path = join(toolchain_root, "bin")

env.Replace(
    CC=join(toolchain_path, "gcc.exe"),
    CXX=join(toolchain_path, "g++.exe"),
    LINK=join(toolchain_path, "g++.exe"),
    AR=join(toolchain_path, "ar.exe"),
    RANLIB=join(toolchain_path, "ranlib.exe"),
)

env["ENV"]["PATH"] = toolchain_path + os.pathsep + env["ENV"].get("PATH", "")

# ==========================================================
# เพิ่ม include / lib paths ของ toolchain
# ==========================================================
env.Append(
    CPPPATH=[
        join(toolchain_root, "include"),
        join(toolchain_root, "include", "SDL2")
    ],
    LIBPATH=[join(toolchain_root, "lib")],
)

# ==========================================================
# โหลด build_flags มาตรฐาน (std_build_flags.json)
# ==========================================================
std_flags_file = join(env['PROJECT_DIR'], "std_build_flags.json")
std_flags = []
try:
    with open(std_flags_file, "r", encoding="utf-8") as f:
        std_flags = json.load(f).get("build_flags", []) or []
except Exception as e:
    print(f"[WARNING] Cannot read {std_flags_file}: {e}")

# ==========================================================
# โหลด build_flags จาก board JSON
# ==========================================================
board_name = env.GetProjectConfig().get("env:" + env["PIOENV"], "board_name", None)
board_flags = []
if board_name:
    board_file = join(env['PROJECT_DIR'], "platform", "boards", f"{board_name}.json")
    try:
        with open(board_file, "r", encoding="utf-8") as f:
            board_flags = json.load(f).get("build", {}).get("build_flags", []) or []
    except Exception as e:
        print(f"[WARNING] Cannot read {board_file}: {e}")
else:
    print("[INFO] No board_name specified, skipping board flags")

# ==========================================================
# อ่านค่าที่ platformio.ini กำหนดไว้ (รองรับทั้ง string และ list)
# ==========================================================
project_config = env.GetProjectConfig()
ini_flags_raw = project_config.get("env:" + env["PIOENV"], "build_flags", "")

if isinstance(ini_flags_raw, str):
    ini_lines = [x.strip() for x in ini_flags_raw.splitlines() if x.strip()]
elif isinstance(ini_flags_raw, list):
    ini_lines = [str(x).strip() for x in ini_flags_raw if str(x).strip()]
else:
    ini_lines = []

ini_defines = {}
for line in ini_lines:
    if line.startswith("-D"):
        keyval = line[2:].split("=", 1)
        key = keyval[0].strip()
        val = keyval[1].strip() if len(keyval) > 1 else None
        ini_defines[key] = val

# ==========================================================
# รวม flags และป้องกันการ override เฉพาะ LCD_WIDTH/HEIGHT
# ==========================================================
protected_keys = {"LCD_WIDTH", "LCD_HEIGHT"}
all_flags = (std_flags or []) + (board_flags or [])

def remove_protected_flags(flags, protected, ini_def_map):
    out = []
    for flag in flags:
        if isinstance(flag, str) and flag.startswith("-D"):
            name = flag[2:].split("=", 1)[0].strip()
            if name in protected and name in ini_def_map:
                print(f"[INFO] Skip {name} from JSON/std (using platformio.ini value: {ini_def_map[name]})")
                continue
        out.append(flag)
    return out

filtered_std_flags = remove_protected_flags(std_flags, protected_keys, ini_defines)
filtered_board_flags = remove_protected_flags(board_flags, protected_keys, ini_defines)

# ==========================================================
# รวมและ append เข้า environment
# ==========================================================
merged_flags = filtered_std_flags + filtered_board_flags
if merged_flags:
    env.Append(BUILD_FLAGS=merged_flags)
    print(f"[INFO] Appended BUILD_FLAGS ({board_name}): {len(merged_flags)} flags")

# ==========================================================
# แสดงค่าที่ใช้จริง (LCD_WIDTH / LCD_HEIGHT)
# ==========================================================
def get_final_define(name):
    if name in ini_defines:
        return ini_defines[name]
    cpp = env.get("CPPDEFINES", [])
    for d in cpp:
        if isinstance(d, tuple) and d[0] == name:
            return d[1]
        if isinstance(d, str) and d.startswith(name + "="):
            return d.split("=", 1)[1]
    for f in merged_flags:
        if isinstance(f, str) and f.startswith("-D"):
            nm = f[2:].split("=", 1)[0].strip()
            if nm == name:
                parts = f[2:].split("=", 1)
                return parts[1] if len(parts) > 1 else None
    return None

w = get_final_define("LCD_WIDTH")
h = get_final_define("LCD_HEIGHT")
print(f"[INFO] Final LCD_WIDTH = {w}, LCD_HEIGHT = {h} (platformio.ini has priority)")
