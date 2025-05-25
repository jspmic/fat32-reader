CC=gcc
CFLAGS=-Wall
BUILD_DIR=./build
SRC_DIR=./src
DISK=fat32.img
BIN=main
SRC=$(shell ls $(SRC_DIR)/*.c)
SIZE=64

.PHONY: build disk clean

build: disk
	$(CC) $(CFLAGS) $(BIN).c -I $(SRC_DIR) $(SRC) -o $(BUILD_DIR)/$(BIN)
	$(BUILD_DIR)/$(BIN) $(BUILD_DIR)/$(DISK)

disk:
	@if [ -e "$(BUILD_DIR)/$(DISK)" ]; then \
		echo "File '$(DISK)' already exists. Not overwriting."; \
	else \
		echo "Creating disk image '$(DISK)'..."; \
		dd if=/dev/zero of=$(BUILD_DIR)/$(DISK) bs=1M count=$(SIZE); \
		mkfs.fat -F 32 -n "TEST_LABEL" $(BUILD_DIR)/$(DISK); \
		echo "Disk image '$(DISK)' created."; \
	fi

clean:
	rm $(BUILD_DIR)/$(BIN)
