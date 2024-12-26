#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <memory.h>
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


FILE* open_disk(const char* disk_name){
	FILE* fd = fopen(disk_name, "rb"); // READ-ONLY mode
	return fd;
}

BootSector _bootSector; // Global variable to store the MBR

void read_mbr(FILE* disk){
	if (fread(&_bootSector, sizeof(_bootSector), 1, disk) < 0)
		perror("read_mbr");
}

void test_mbr(void){
	printf("JMP: \t\t\t");
	for (int i = 0; i<JMP; i++){
		printf("%.2X ", _bootSector.jmp[i]);
	}

	printf("\nOEM: \t\t\t");
	for (int i = 0; i<OEM; i++){
		printf("%.2X ", _bootSector.oem[i]);
	}

	printf("\nBytes per Sector:\t");
	for (int i = 0; i<WORD; i++){
		printf("%.2X ", _bootSector.bytesPerSector[i]);
	}

	printf("\nSectors per Cluster:\t");
	for (int i = 0; i<BYTE; i++){
		printf("%.2X ", _bootSector.sectorsPerCluster[i]);
	}

	printf("\nReserved Sectors:\t");
	for (int i = 0; i<WORD; i++){
		printf("%.2X ", _bootSector.reservedSectors[i]);
	}

	printf("\nNumber of FATs:\t\t");
	for (int i = 0; i<BYTE; i++){
		printf("%.2X ", _bootSector.numFat[i]);
	}

	printf("\nRoot Entries:\t\t");
	for (int i = 0; i<WORD; i++){
		printf("%.2X ", _bootSector.rootEntry[i]);
	}

	printf("\nSmall Sectors:\t\t");
	for (int i = 0; i<WORD; i++){
		printf("%.2X ", _bootSector.smallSectors[i]);
	}

	printf("\nMedia Type:\t\t");
	for (int i = 0; i<BYTE; i++){
		printf("%.2X ", _bootSector.mediaType[i]);
	}

	printf("\nSectors per FAT:\t");
	for (int i = 0; i<WORD; i++){
		printf("%.2X ", _bootSector.sectorsPerFat[i]);
	}

	printf("\nSectors per Track:\t");
	for (int i = 0; i<WORD; i++){
		printf("%.2X ", _bootSector.sectorsPerTrack[i]);
	}

	printf("\nNumber of Heads:\t");
	for (int i = 0; i<WORD; i++){
		printf("%.2X ", _bootSector.numHeads[i]);
	}

	printf("\nHidden Sectors:\t\t");
	for (int i = 0; i<DWORD; i++){
		printf("%.2X ", _bootSector.hiddenSectors[i]);
	}

	printf("\nLarge Sectors:\t\t");
	for (int i = 0; i<DWORD; i++){
		printf("%.2X ", _bootSector.largeSectors[i]);
	}

	printf("\nPhysical Disk Number:\t");
	for (int i = 0; i<BYTE; i++){
		printf("%.2X ", _bootSector.physicalDiskNumber[i]);
	}

	printf("\nCurrent Head:\t\t");
	for (int i = 0; i<BYTE; i++){
		printf("%.2X ", _bootSector.currentHead[i]);
	}

	printf("\nSignature:\t\t");
	for (int i = 0; i<BYTE; i++){
		printf("%.2X ", _bootSector.signature[i]);
	}

	printf("\nVolume Serial Number:\t");
	for (int i = 0; i<VOLUMESER_NUM; i++){
		printf("%.2X ", _bootSector.volumeSerialNumber[i]);
	}

	printf("\nVolume Label:\t\t");
	for (int i = 0; i<VOLUME_LABEL; i++){
		printf("%c ", _bootSector.volumeLabel[i]);
	}

	printf("\nSystem ID:\t\t");
	for (int i = 0; i<SYSTEM_ID; i++){
		printf("%c ", _bootSector.systemID[i]);
	}

	/* printf("\nBootStrap:\t\t"); */
	/* for (int i = 0; i<BOOTSTRAP; i++){ */
	/* 	printf("%.2X ", _bootSector.bootstrap[i]); */
	/* } */

	printf("\nEND: \t\t\t");
	for (int i = 0; i<END; i++){
		printf("%.2X ", _bootSector.end[i]);
	}
}

int main(int argc, char** argv){
	if (argc != 2){
		printf("Usage: <program> <disk_name>\n");
		return 1;
	}
	FILE* fd = open_disk(argv[argc-1]);

	read_mbr(fd); // Reading MBR Boot Code

	test_mbr();
	
	fclose(fd);
	return 0;
}
