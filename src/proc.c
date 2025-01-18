#include "header.h"
#include <stdint.h>
#include <stdio.h>

uint32_t FATSEC_SIZE;

FILE* open_disk(const char* disk_name){
	FILE* fd = fopen(disk_name, "rb"); // READ-ONLY mode
	return fd;
}

bool read_bootCode(FILE* disk, struct BootSector *_bootSector){
	if (fread(_bootSector, sizeof(*(_bootSector)), 1, disk) < 0){
		perror("read_bootCode");
		return false;
	}
	FATSEC_SIZE = (_bootSector->BPB_NumFATs)*(_bootSector->BPB_FatSz32);
	return true;
}

bool read_sector(FILE* disk, struct BootSector *_bootSector, uint32_t lba, uint32_t count, void *bufferOut){
	// lba: sector number to begin from
	// count: number of sectors to read
	bool ok = true;
	ok = ok && (fseek(disk, lba*(_bootSector->BPB_BytesPerSec), SEEK_SET) == 0);
	ok = ok && (fread(bufferOut, _bootSector->BPB_BytesPerSec, count, disk) == count);
	return ok;
}

void test_mbr(struct BootSector *_bootSector){
	printf("JMP: \t\t\t");
	for (int i = 0; i<JMP; i++){
		printf("%.2X ", _bootSector->BS_jmpBoot[i]);
	}

	printf("\nOEM: \t\t\t");
	for (int i = 0; i<OEM; i++){
		printf("%c", _bootSector->BS_OEM[i]);
	}

	printf("\nBytes per Sector:\t%d", _bootSector->BPB_BytesPerSec);

	printf("\nSectors per Cluster:\t%X", _bootSector->BPB_SecPerClus);

	printf("\nReserved Sectors:\t%d", _bootSector->BPB_RsvdSecCnt);

	printf("\nNumber of FATs:\t\t%d", _bootSector->BPB_NumFATs);
	printf("\nBoot Sector(backup):\t%X", _bootSector->BPB_BkBootSec);

	printf("\nRoot Entries:\t\t%d", _bootSector->BPB_RootEntCnt);

	printf("\nSmall Sectors:\t\t%d", _bootSector->BPB_TotSec16);

	printf("\nMedia Type:\t\t%X", _bootSector->BPB_Media);

	printf("\nSectors per FAT:\t%d", _bootSector->BPB_FatSz32);

	printf("\nSectors per Track:\t%X", _bootSector->BPB_SecPerTrk);

	printf("\nNumber of Heads:\t%X", _bootSector->BPB_NumHeads);

	printf("\nHidden Sectors:\t\t%d", _bootSector->BPB_HiddSec);

	printf("\nLarge Sectors:\t\t%d", _bootSector->BPB_TotSec32);

	printf("\nPhysical Disk Number:\t%X", _bootSector->BS_DrvNum);

	printf("\nCurrent Head:\t\t%X", _bootSector->BS_Reserved1);

	printf("\nSignature:\t\t%X", _bootSector->BS_BootSig);

	printf("\nVolume Serial Number:\t%X", _bootSector->BS_VolID);

	printf("\nVolume Label:\t\t");
	for (int i = 0; i<VOLUME_LABEL; i++){
		printf("%c", _bootSector->BS_VolLab[i]);
	}

	printf("\nSystem ID:\t\t");
	for (int i = 0; i<SYSTEM_ID; i++){
		printf("%c", _bootSector->BS_FilSysType[i]);
	}

	/* printf("\nBootStrap:\t\t"); */
	/* for (int i = 0; i<BOOTSTRAP; i++){ */
	/* 	printf("%X ", _bootSector.bootstrap[i]); */
	/* } */

	printf("\nEND: \t\t\t%X", htobe16(_bootSector->Signature_word));
}

uint32_t count_clusters(struct BootSector *_bootSector){
	uint16_t RootDirSectors = ((_bootSector->BPB_RootEntCnt * 32) + (_bootSector->BPB_BytesPerSec-1)) / _bootSector->BPB_BytesPerSec;
	uint32_t fatSz, totSec, dataSec, countClusters;
	if (_bootSector->BPB_FATSz16 != 0){
		fatSz = _bootSector->BPB_FATSz16;
	}
	else{
		fatSz = _bootSector->BPB_FatSz32;
	}

	if (_bootSector->BPB_TotSec16 != 0){
		totSec = _bootSector->BPB_TotSec16;
	}
	else {
		totSec = _bootSector->BPB_TotSec32;
	}

	dataSec = totSec - (_bootSector->BPB_RsvdSecCnt + (_bootSector->BPB_NumFATs * fatSz) + RootDirSectors);
	countClusters = dataSec/(_bootSector->BPB_SecPerClus);
	return countClusters;
}

bool isFat32(uint32_t clusters){
	if (clusters < 4085 || clusters < 65525){
		return false;
	}
	return true;
}
