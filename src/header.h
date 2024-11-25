enum FAT32_SECTOR{
	BOOT_START				= 0, 		// The MBR beginning
	BOOT_END				= 446, 		// The MBR ending
	PARTITION_DESCRIPTION	= 16,
	TYPE_CODE				= 5,		// The type code is the 5th byte of the description
	LBA_BEGIN				= 9,
	LBA_LAST				= 12,
	FAT32_CODE				= 0x0B,
	FAT32_CODE2				= 0x0C,
	FIRST_LAST_BYTE			= 0x55,		// The first among the 2 last bytes of a sector
	SECOND_LAST_BYTE		= 0xAA, 	// The very last byte of a sector
};
