#ifndef HDR
#define HDR

// A sector is considered to be 512 bytes large
#include <stdint.h>
#define SECTOR_SIZE 512

// FAT32 partition table is of size 64 bytes
#define PARTITION_TABLE 64

typedef struct{
	uint32_t* BOOT_CODE;
} Disk;

enum FAT32_SECTOR{
	MBR						= 510, 		// The MBR Length
	PARTITION_DESCRIPTION	= 16,
	TYPE_CODE				= 5,		// The type code is the 5th byte of the description
	LBA_BEGIN				= 9,
	LBA_LAST				= 12,
	FAT32_CODE				= 0x0B,
	FAT32_CODE2				= 0x0C,
	FIRST_LAST_BYTE			= 0x55,		// The first among the 2 last bytes of a sector
	SECOND_LAST_BYTE		= 0xAA, 	// The very last byte of a sector
};


#endif
