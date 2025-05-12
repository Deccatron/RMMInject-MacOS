# RMMInject-MacOS

**RMMInject-MacOS** is a lightweight and effective macOS dylib injector tailored specifically for injecting custom `.dylib` files into **RobloxPlayer**. Designed with stealth in mind, this tool leverages `DYLD_INSERT_LIBRARIES` for clean and undetected injection, making it ideal for advanced debugging, modding, or research use.


> ⚠️ **Disclaimer**: This tool is intended for educational and development purposes only. Misuse may violate Roblox's Terms of Service or local laws. Use responsibly and dont be a retard, if your gonna make exploits dont get caught ;).


---

## 🚀 Features

* ✅ Minimal, efficient codebase
* 🔐 Bypasses detection flags by using environment variable injection
* 🛠️ Simple configuration — no bloat, no third-party dependencies
* 💻 macOS native, tested on recent versions of macOS with Roblox

---

## 🧠 How It Works

RMMInject-MacOS sets the following environment variables before launching the target app:

* `DYLD_INSERT_LIBRARIES` — points to your `.dylib` to load
* `DYLD_FORCE_FLAT_NAMESPACE` — ensures full symbol access for better compatibility

Once set, it uses `execl()` to cleanly start RobloxPlayer with your dylib injected at runtime.

---

## 🛠️ Setup & Usage

### ✅ Requirements

* macOS
* Xcode (or any g++/clang compiler)
* A valid `.dylib` compiled for macOS

### 📦 Build

Compile using `g++` or within Xcode:

```bash
g++ -o rmminject main.cpp
```

### 🚨 Usage

```bash
./rmminject
```

By default, the paths are hardcoded:

```cpp
const char* dylib_path = "/Users/youruser/path/to/Dumper.dylib";
const char* target_app_path = "/Applications/Roblox.app/Contents/MacOS/RobloxPlayer";
```

You can also modify `main()` to take arguments instead, or adapt the following example:

```cpp
./rmminject /path/to/myhack.dylib /Applications/Roblox.app/Contents/MacOS/RobloxPlayer
```

---

## 📂 Example Output

```text
Using paths:
Dylib: /Users/dexter/Library/Developer/Xcode/.../Dumper.dylib
Target: /Applications/Roblox.app/Contents/MacOS/RobloxPlayer
Injecting dylib: ... into: ...
```

---

## 🔒 Notes

* Ensure your `.dylib` is compiled for the correct architecture (e.g. ARM64 vs x86\_64).
* Do **not** run this tool outside of a sandbox or test environment unless you know what you're doing.
* If Roblox updates or modifies its loading process, this may stop working. Keep your injector up to date.

---

## 📜 License

This project is released under the MIT License. See `LICENSE` for details.

---
