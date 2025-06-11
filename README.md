# 🛡️ C Text File Manager – Vulnerability Demonstration Project

This project is a simple **C-based text file manager** designed to simulate common user interactions such as login, file creation, deletion, and reading. It is built as a standalone executable (`main.c`) and **intentionally includes multiple security vulnerabilities** for educational purposes.

---

## ⚙️ Features

- Simple user login system (insecure by design)
- Create, write, and delete text files
- View user logs and session history
- Command-based text search system
- Single source file (`main.c`) with ~700–800 lines

---

## ❗ Known Vulnerabilities (Intentionally Added)

| Type                 | Location           | Description |
|----------------------|--------------------|-------------|
| Buffer Overflow       | `gets()` usage     | Input without bounds check |
| Heap Overflow         | `strcpy()`         | Unsafe copy to malloc'ed buffer |
| Format String Attack  | `printf(user_input)` | No format specifier |
| Command Injection     | `system()`         | Unvalidated input used in shell |
| Use-After-Free        | File pointer reuse | After freeing file memory |
| Function Pointer Hijack | Function pointer struct | Attacker can overwrite behavior |

---

## 🧪 How to Build and Run

### Compile:
```bash
gcc main.c -o file_manager.exe
