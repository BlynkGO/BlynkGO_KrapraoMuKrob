import os
import shutil
from os.path import join

Import("env")

# folder build และ toolchain
build_dir = env.subst("$BUILD_DIR")
toolchain_bin = join(env['PROJECT_DIR'], "toolchain", "bin")

# DLL list ที่ต้อง copy
dlls = ["SDL2.dll", "libgcc_s_seh-1.dll", "libstdc++-6.dll", "libwinpthread-1.dll"]

for dll in dlls:
    src = join(toolchain_bin, dll)
    dst = join(build_dir, dll)
    if os.path.exists(src):
        shutil.copy2(src, dst)
