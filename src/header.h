#ifndef HDR
#define HDR

// A sector is considered to be 512 bytes large
#include <stdint.h>
#define SECTOR_SIZE 512

// FAT32 partition table is of size 64 bytes
#define PARTITION_TABLE 64

#define WORD 2
#define BYTE 1

enum{
	LBA_START = 0,
	DWORD = WORD*2,
	MBR_SIZE = 512,
	JMP = 3,
	OEM = 8,
	VOLUMESER_NUM = 4,
	VOLUME_LABEL = 11,
	SYSTEM_ID = 8,
	EXBIOS = 26,
	BOOTSTRAP = 448,
	END = 2
};

typedef struct{
	// Prologue fields
	uint8_t jmp[JMP];
	uint8_t oem[OEM];

	// BIOS fields
	uint8_t bytesPerSector[WORD];
	uint8_t sectorsPerCluster[BYTE];
	uint8_t reservedSectors[WORD];
	uint8_t numFat[BYTE];
	uint8_t rootEntry[WORD];
	uint8_t smallSectors[WORD];
	uint8_t mediaType[BYTE];
	uint8_t sectorsPerFat[WORD];
	uint8_t sectorsPerTrack[WORD];
	uint8_t numHeads[WORD];
	uint8_t hiddenSectors[DWORD]; // DWORD = WORD*2
	uint8_t largeSectors[DWORD];
	uint8_t physicalDiskNumber[BYTE];
	uint8_t currentHead[BYTE];
	uint8_t signature[BYTE];
	uint8_t volumeSerialNumber[VOLUMESER_NUM];
	uint8_t volumeLabel[VOLUME_LABEL];
	uint8_t systemID[SYSTEM_ID];

	// Concluding fields
	uint8_t bootstrap[BOOTSTRAP];
	uint8_t end[END];

} BootSector;


#endif
