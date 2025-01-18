#include "header.h"

FILE* open_disk(const char* disk_name){
	FILE* fd = fopen(disk_name, "rb"); // READ-ONLY mode
	return fd;
}

bool read_bootCode(FILE* disk, struct BootSector *_bootSector){
	if (fread(_bootSector, sizeof(*(_bootSector)), 1, disk) < 0){
		perror("read_mbr");
		return false;
	}
	return true;
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

	printf("\nBytes per Sector:\t%X", _bootSector->BPB_BytesPerSec);

	printf("\nSectors per Cluster:\t%X", _bootSector->BPB_SecPerClus);

	printf("\nReserved Sectors:\t%X", _bootSector->BPB_RsvdSecCnt);

	printf("\nNumber of FATs:\t\t%X", _bootSector->BPB_NumFATs);

	printf("\nRoot Entries:\t\t%X", _bootSector->BPB_RootEntCnt);

	printf("\nSmall Sectors:\t\t%X", _bootSector->BPB_TotSec16);

	printf("\nMedia Type:\t\t%X", _bootSector->BPB_Media);

	printf("\nSectors per FAT:\t%X", _bootSector->BPB_FATSz16);

	printf("\nSectors per Track:\t%X", _bootSector->BPB_SecPerTrk);

	printf("\nNumber of Heads:\t%X", _bootSector->BPB_NumHeads);

	printf("\nHidden Sectors:\t\t%X", _bootSector->BPB_HiddSec);

	printf("\nLarge Sectors:\t\t%X", _bootSector->BPB_TotSec32);

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
