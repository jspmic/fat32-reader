#include <stdint.h>
#include <stdio.h>
#include <endian.h>
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

	printf("\nBytes per Sector:\t%d", _bootSector.bytesPerSector);

	printf("\nSectors per Cluster:\t%X", _bootSector.sectorsPerCluster);

	printf("\nReserved Sectors:\t%d", _bootSector.reservedSectors);

	printf("\nNumber of FATs:\t\t%d", _bootSector.numFat);

	printf("\nRoot Entries:\t\t%d", _bootSector.rootEntry);

	printf("\nSmall Sectors:\t\t%X", _bootSector.smallSectors);

	printf("\nMedia Type:\t\t%X", _bootSector.mediaType);

	printf("\nSectors per FAT:\t%d", _bootSector.sectorsPerFat);

	printf("\nSectors per Track:\t%X", _bootSector.sectorsPerTrack);

	printf("\nNumber of Heads:\t%X", _bootSector.numHeads);

	printf("\nHidden Sectors:\t\t%X", _bootSector.hiddenSectors);

	printf("\nLarge Sectors:\t\t%X", _bootSector.largeSectors);

	printf("\nPhysical Disk Number:\t%X", _bootSector.physicalDiskNumber);

	printf("\nCurrent Head:\t\t%X", _bootSector.currentHead);

	printf("\nSignature:\t\t%X", _bootSector.signature);

	printf("\nVolume Serial Number:\t%X", _bootSector.volumeSerialNumber);

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
	/* 	printf("%X ", _bootSector.bootstrap[i]); */
	/* } */

	printf("\nEND: \t\t\t%X", _bootSector.end);
}

int main(int argc, char** argv){
	if (argc != 2){
		printf("Usage: <program> <disk_name>\n");
		return 1;
	}
	FILE* fd = open_disk(argv[argc-1]);

	read_mbr(fd); // Reading MBR Boot Code

	test_mbr(); // For testing purposes
	
	fclose(fd);
	return 0;
}
