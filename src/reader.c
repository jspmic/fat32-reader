#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <endian.h>
#include <assert.h>
#include "header.h"


/*
 * @description: This is a FAT32 disk reader, that uses Logical Block Addressing(LBA).
 * @reference: For more info, read:
	 * - https://www.pjrc.com/tech/8051/ide/fat32.html
	 * - https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system
*/

/*
 This section contains the basic functions which we will work with
 to implement the reader
*/

int open_disk(const char* disk_name){
	int fd = open(disk_name, O_RDONLY); // READ-ONLY mode
	if (fd == -1){
		printf("Disk image not found!");
		perror("open_disk");
		exit(1);
	}
	return fd;
}

/*
 * args:
 * - fd: file descriptor
 * - start: the starting point of reading
*/

void read_disk(const int fd, const int start, const int end, uint32_t* buffer){
	lseek(fd, 0, 0);
	if(lseek(fd, start, 0) < 0)
		perror("lseek - read_disk");

	int size = end-start;
	int l = read(fd, buffer, size);

	if (l==-1)
		perror("read - read_disk");

	for (int i = 0; i<size; i++){
		buffer[i] = htobe32(buffer[i]);
	}
	lseek(fd, 0, 0);
}

int main(int argc, char** argv){
	if (argc != 2){
		printf("Usage: <program> <disk_name>\n");
		return 1;
	}
	int fd = open_disk(argv[argc-1]);
	if (fd > 0)
		printf("Opened disk successfully!\n");

	int end = 11; // Eleventh byte
	int start = 1; // Second byte
	int size = end-start;
	uint32_t* buffer = malloc(sizeof(uint32_t)*size);
	read_disk(fd, start, end, buffer);
	for (int i = 0; i<((size%sizeof(uint32_t))+1); i++)
		printf("%.2X ", buffer[i]);
	printf("\n");
	close(fd);
	return 0;
}
