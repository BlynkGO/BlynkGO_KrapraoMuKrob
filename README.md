# BlynkGO_KrapraoMuKrob
## **"The Ultimate GUI Development Engine for BeeNeXT"**

**BlynkGO KrapraoMuKrob** is a high-performance Windows simulator for **BlynkGO v5**.  
It allows you to develop, preview, and test your touch-screen UI on PC instantly  
using **Arduino-style code** before deploying to real hardware.

---

## 🚀 Why BlynkGO KrapraoMuKrob?
* **⚡ 10x Faster Development:**  
No more long waiting for flashing. Build and run in seconds!

* **📟 Arduino Logic on PC:**  
Use your familiar C/C++ Arduino code to create complex Windows Applications.

* **🛠️ One Code, Multiple Devices:**  
Write once and run on **PC Simulator**, **Web (Wasm)**, and **BeeNeXT Hardware**.

* **🌐 Full Connectivity:**  
Connect to real MCUs via **COM Port**, or use **MQTT** and **HTTP Client** directly from your PC app.

---

# 📦 Installation

## 1. Install Python
* Download Python for Windows: [https://www.python.org/downloads/windows/](https://www.python.org/downloads/windows/)
* **⚠️ IMPORTANT:** Disable Antivirus & Windows Defender before installation.
* **⚠️ IMPORTANT:** Make sure to check **"Add Python to PATH"** during installation.

## 2. Install Visual Studio Code
* Download VS Code: [https://code.visualstudio.com/](https://code.visualstudio.com/)
* Install it on your system.

## 3. Install PlatformIO Extension in VS Code
* Open VS Code → go to **Extensions** → search for `PlatformIO IDE` → **Install**.

## 4. Install Git
* Download Git for Windows: [https://git-scm.com/install/windows](https://git-scm.com/install/windows)
* Install Git on your system.

## 5. Clone BlynkGO_KrapraoMuKrob
* Open a terminal (CMD/PowerShell).
* **Navigate to the folder** where you want to clone the project, for example:
  ```bash
  cd C:\MyProjects
  ```
* Run the clone command:
  ```bash
  git clone https://github.com/BlynkGO/BlynkGO_KrapraoMuKrob
  cd BlynkGO_KrapraoMuKrob
  ```

**💡 Note:**
* To protect your project in the **src/** folder from being overwritten during future updates, run the following command to ignore local changes:
  ```bash
  git update-index --skip-worktree src/*
  ```
* For future updates from the repository, use:
  ```bash
  git pull
  ```

## 6. Open the project in VS Code
* Open VS Code → **File → Open Folder** → select the folder **BlynkGO_KrapraoMuKrob**.
* Wait for **PlatformIO** to load and set up the environment completely.

## 7. Ready to Use BlynkGO_KrapraoMuKrob
* You can select/change the board in `platformio.ini`.
* Build and upload/run the project normally through PlatformIO, and use the generated graphics in your BeeNeXT touchscreen projects.
> (First time: the toolchain and other necessary tools will be installed automatically.)

![kmk_build](kmk_build.png)

---

## 🚀 Create a New BlynkGO Project
* In VS Code, **open the integrated terminal**:
  * Go to the menu: `Terminal → New Terminal` (or use shortcut `` Ctrl+` ``).
* Run the command:
  ```bash
  > new_blynkgo
  ```
* In the `src` folder, a new `main.cpp` file will be automatically created:
  ```cpp
  #include <BlynkGOv5.h>

  void setup(){
    Serial.begin(9600); Serial.println();
    BlynkGO.begin();
  }

  void loop(){
    BlynkGO.update();
  }
  ```
*If a `main.cpp` file already exists, it will be automatically renamed to `main.cpp_YYYYMMDD_HHMMSS`.*

---

## 📖 How to convert Image for using in your project

### 1️⃣ Prepare Your Images
Place the image files (PNG, JPG, BMP) into the folder: `src/images`

### 2️⃣ Convert Standard Images
Open a Terminal in the `src/images` folder and type:
```bash
> imgconv filename.png
# or
> imgconv filename.jpg
> imgconv filename.bmp
```

### 3️⃣ Convert PNG Images with Transparency
To preserve transparency, add the `-t` option:
```bash
> imgconv filename.png -t
```
🖼️ *The converted files will be saved in: `src/images/output`*

### 4️⃣ Set Your Own Output Filename
Add the `-o` option followed by the desired name:
```bash
> imgconv filename.png -o desired_name
```

---

## 📖 How to convert TrueType Font for using in your project

### 1️⃣ Prepare Your TrueType Font (.ttf)
Place the `.ttf` files into the folder: `src/fonts`

### 2️⃣ Convert Font
Open a Terminal in the `src/fonts` folder and type:
```bash
> fontconv --font {FONT}.ttf --size {SIZE}
```
*Example:* `fontconv --font myfont.ttf --size 25`

### 3️⃣ Convert Numeric & Math Symbols (Minimal Size)
To keep file size small, add the `-num` option:
```bash
> fontconv --font {FONT}.ttf --size {SIZE} -num
```

### 4️⃣ Convert Thai Fonts (English + Thai + Numeric)
Add the `-thai` option:
```bash
> fontconv --font {THAI_FONT}.ttf --size {SIZE} -thai
```
> [!IMPORTANT]
> Thai Font (.ttf) must comply with the **BlynkGOv5 Font** standard.

### 5️⃣ Convert Lao Fonts (English + Lao + Numeric)
Add the `-lao` option:
```bash
> fontconv --font {LAO_FONT}.ttf --size {SIZE} -lao
```
> [!IMPORTANT]
> Lao Font (.ttf) must comply with the **BlynkGOv5 Font** standard.

### 6️⃣ Set Your Own Output Filename
Add the `-o` option:
```bash
> fontconv --font {FONT}.ttf --size {SIZE} -o desired_name.c
```

---

## 🤝 Community & Support
* **Facebook Group:** [BlynkGO Community](https://www.facebook.com/groups/blynkgo)
* **Official Website:** [BlynkGO.com](https://www.blynkgo.com)

---
Developed with ❤️ by the BlynkGO Team.
