#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "header.h"

/*
 * @description: This is a FAT32 disk reader, that uses Logical Block Addressing(LBA).
 * @reference: For more info, read:
	 * - https://www.pjrc.com/tech/8051/ide/fat32.html
	 * - https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system
*/

// A sector is considered to be 512 bytes large
#define SECTOR_SIZE 512

// FAT32 partition table is of size 64 bytes
#define PARTITION_TABLE 64

/*
 This section contains the basic functions which we will work with
 to implement the reader
*/
int open_disk(const char* disk_name){
	int fd = open(disk_name, O_RDONLY);
	if (fd == -1){
		perror("read_disk");
		exit(1);
	}
	return fd;
}

// Return start position + end - eof
int read_disk(int fd, unsigned char buffer[], int start, int end){
	int l = read(fd, buffer, end-start);
	if (l==-1){
		perror("read_disk");
		return -1;
	}
	return l;
}

void close_disk(int fd){
	close(fd);
}

/*
 This section contains various procedures to read safely
 from a given disk file.
*/

// Read the n-th partition(note that only 4 partitions are available)
void read_partition(int fd, unsigned char buffer[]){
	int pos;
	if (fd < BOOT_END)
		pos = read_disk(fd, buffer, BOOT_START+BOOT_END, BOOT_END+PARTITION_DESCRIPTION);
	else
		pos = read_disk(fd, buffer, 0, PARTITION_DESCRIPTION);

	if (pos == -1){
		perror("read_partition");
		return;
	}
}

int main(int argc, char** argv){
	if (argc != 2){
		printf("Usage: <program> <disk_name>\n");
		return 1;
	}
	int fd = open_disk(argv[argc-1]);
	unsigned char buffer[PARTITION_DESCRIPTION];
	read_partition(fd, buffer);
	printf("It is FAT32 %s\n", buffer);
	close_disk(fd);
	return 0;
}
