CC=gcc
CFLAGS=-Wall
BUILD_DIR=./build
DISK=fat32_disk.img
SRC=./src/reader.c

.PHONY: build disk clean

build: disk
	$(CC) $(CFLAGS) $(SRC) -o $(BUILD_DIR)/a.out
	$(BUILD_DIR)/a.out

disk:
	mkdir -p $(BUILD_DIR)
	dd if=/dev/zero of=$(BUILD_DIR)/$(DISK) bs=1M count=64

clean:
	rm -f $(BUILD_DIR)/$(DISK) $(BUILD_DIR)/a.out
