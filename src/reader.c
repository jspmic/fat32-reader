#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
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
	int fd = open(disk_name, O_RDONLY, 0);
	if (fd == -1){
		perror("open_disk");
		exit(1);
	}
	// Place at the end of the MBR
	if (lseek(fd, BOOT_END, 0) == -1){
		perror("open_disk");
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

/*
 This section contains various procedures to read safely
 from a given disk file.
*/

// Read the n-th partition(note that only 4 partitions are available)
void read_partition_description(int fd, unsigned char buffer[], int n){
	assert(n > 0);
	lseek(fd, n*PARTITION_DESCRIPTION, 0);
	int pos = read_disk(fd, buffer, 0, PARTITION_DESCRIPTION);

	if (pos == -1)
		return;
	if (lseek(fd, BOOT_END, 0) == -1)
		perror("read_partition_description");
}

int main(int argc, char** argv){
	if (argc != 2){
		printf("Usage: <program> <disk_name>\n");
		return 1;
	}
	int fd = open_disk(argv[argc-1]);
	unsigned char buffer[PARTITION_DESCRIPTION];
	read_partition_description(fd, buffer, 1);
	for (int i = 0; i<PARTITION_DESCRIPTION; i++)
		printf("%x ", buffer[i]);
	printf("\n");
	close(fd);
	return 0;
}
