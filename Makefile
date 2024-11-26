CC=gcc
CFLAGS=-Wall
BUILD_DIR=./build
DISK=fat32.img
DISK2=fat32_disk.img
SRC=./src/reader.c
SIZE=64

.PHONY: build disk clean

build: disk
	$(CC) $(CFLAGS) $(SRC) -o $(BUILD_DIR)/a.out
	$(BUILD_DIR)/a.out $(BUILD_DIR)/$(DISK)

disk:
	@if [ -e "$(BUILD_DIR)/$(DISK)" ]; then \
		echo "File '$(DISK)' already exists. Not overwriting."; \
	else \
		echo "Creating disk image '$(DISK)'..."; \
		dd if=/dev/zero of=$(BUILD_DIR)/$(DISK) bs=1M count=$(SIZE); \
		mkfs.fat -F 32 $(BUILD_DIR)/$(DISK); \
		echo "Disk image '$(DISK)' created."; \
	fi

clean:
	@if [ -e "$(BUILD_DIR)/$(DISK)" ]; then \
		rm -f $(BUILD_DIR)/$(DISK) $(BUILD_DIR)/a.out; \
	else \
		echo "File '$(DISK)' doesn't exists."; \
	fi
