#ifndef HDR
#define HDR

// A sector is considered to be 512 bytes large
#include <stdint.h>

enum{
	JMP = 3,
	OEM = 8,
	VOLUMESER_NUM = 4,
	VOLUME_LABEL = 11,
	SYSTEM_ID = 8,
	BOOTSTRAP = 448,
};

typedef struct{
	// Prologue fields
	uint8_t jmp[JMP];
	uint8_t oem[OEM];

	// BIOS fields
	uint16_t bytesPerSector;
	uint8_t sectorsPerCluster;
	uint16_t reservedSectors;
	uint8_t numFat;
	uint16_t rootEntry;
	uint16_t smallSectors;
	uint8_t mediaType;
	uint16_t sectorsPerFat;
	uint16_t sectorsPerTrack;
	uint16_t numHeads;
	uint32_t hiddenSectors;
	uint32_t largeSectors;
	uint8_t physicalDiskNumber;
	uint8_t currentHead;
	uint8_t signature;
	uint32_t volumeSerialNumber;
	uint8_t volumeLabel[VOLUME_LABEL];
	uint8_t systemID[SYSTEM_ID];

	// Epilogue fields
	uint8_t bootstrap[BOOTSTRAP];
	uint16_t end;

}__attribute__((packed)) BootSector;


#endif
