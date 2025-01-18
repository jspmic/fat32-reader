#ifndef HDR
#define HDR

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <endian.h>
#include <stdbool.h>


enum{
	JMP = 3,
	OEM = 8,
	SECTOR_SIZE=512,
	VOLUME_LABEL = 11,
	SYSTEM_ID = 8,
	BOOTSTRAP = 420,
};

struct BootSector{
	// Prologue fields
	uint8_t BS_jmpBoot[JMP];
	uint8_t BS_OEM[OEM];

	// BIOS fields
	uint16_t BPB_BytesPerSec;
	uint8_t BPB_SecPerClus;
	uint16_t BPB_RsvdSecCnt;
	uint8_t BPB_NumFATs;
	uint16_t BPB_RootEntCnt;
	uint16_t BPB_TotSec16;
	uint8_t BPB_Media;
	uint16_t BPB_FATSz16;
	uint16_t BPB_SecPerTrk;
	uint16_t BPB_NumHeads;
	uint32_t BPB_HiddSec;
	uint32_t BPB_TotSec32;

	uint32_t BPB_FatSz32;
	uint16_t BPB_ExtFlags;
	uint16_t BPB_FSVer;
	uint32_t BPB_RootClus;
	uint16_t BPB_FSInfo;
	uint16_t BPB_BkBootSec;
	uint8_t BPB_Reserved[12];

	uint8_t BS_DrvNum;
	uint8_t BS_Reserved1;
	uint8_t BS_BootSig;
	uint32_t BS_VolID;
	uint8_t BS_VolLab[VOLUME_LABEL];
	uint8_t BS_FilSysType[SYSTEM_ID];

	// Epilogue fields
	uint8_t bootstrap[BOOTSTRAP];
	uint16_t Signature_word;

}__attribute__((packed));

struct FAT{
	uint8_t padding[SECTOR_SIZE];
}__attribute__((packed));

extern bool read_bootCode(FILE* disk, struct BootSector *_bootSector);

extern FILE* open_disk(const char* disk_name);

extern void test_mbr(struct BootSector *_bootSector);

extern uint32_t count_clusters(struct BootSector *_bootSector);

extern bool isFat32(uint32_t clusters);

#endif
