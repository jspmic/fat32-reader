#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/*
 * @description: This is a FAT32 disk reader, that uses Logical Block Addressing(LBA).
 * @reference: For more info, read:
	 * - https://www.pjrc.com/tech/8051/ide/fat32.html
	 * - https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system
*/

// Experimental disk image name(must be FAT32)
#define DISK_NAME "fat32.img"

// A sector is considered to be 512 bytes large
#define SECTOR_SIZE 512

// A partition is of size 16 bytes
#define PARTITION_SIZE 16

// FAT32 partition table is of size 64 bytes
#define PARTITION_TABLE 64


int main(int argc, char** argv){
	printf("Hey, dumb %x!\n", FIRST_LAST_BYTE);
	return 0;
}
