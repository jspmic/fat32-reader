# 📂 FAT32 Reader

A lightweight, work-in-progress FAT32 reader written in C.
This tool reads a raw disk image or block device on UNIX-like systems and inspects its partition layout and FAT32 filesystem metadata.

⚠️ This is a side project I work on occasionally — it's in the early stages, and the codebase is kept intentionally simple (not yet scalable or fully modular).

# 🚀 What It Does

- Opens a disk or image file (/dev/sdX, .img, etc.)

- Parses and prints:
    - Master Boot Record (MBR)
    - FAT32 Boot Sector info
    - Number of clusters, filesystem type, etc.

- Verifies if the volume is FAT32

# 📁 Project Structure

```
fat32-reader/
├── build/          # Disk image files and build files
├── src/
│   ├── proc.c      # All core procedures (open_disk, isFat32, read_bootCode, ...)
│   └── header.h    # Header declarations
├── main.c          # Entry point: uses the functions to parse the disk
├── Makefile        # Simple build script
```
All logic is centralized in `proc.c` for now — no abstraction or modular design yet. This might evolve if I dedicate more time to it in the future.

# 🧪 Testing

Currently, there are no automated tests. I plan 
to add some later when time allows.
In the meantime, basic validation is done by manually running the program on known-good disk images.

# 🛠 Build and Run
## 🛠 Build
```bash
make
```
### ▶️ Run
Runs automatically, or:
```bash
./build/main
```

# ⚙️ Features (Planned / Potential)

- Better error handling
- Unit tests for parsing routines
- Extensible support for FAT16/FAT12
- Recursive directory listing
# ❗ Note

This is not production-grade and should be used carefully — especially when pointing it to real block devices (/dev/sdX). Always prefer running it on image files unless you know what you’re doing.

# 📜 License

MIT License — use, fork, modify freely. No warranties.
