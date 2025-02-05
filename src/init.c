/*
 * @description: This is a FAT32 disk reader, that uses Logical Block Addressing(LBA).
 * @reference: For more info, read:
	 * - https://www.pjrc.com/tech/8051/ide/fat32.html
	 * - https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system
*/

/*
 This section contains the main entry point of the FAT32 reader(for testing)
 but you may use this to see how the reader is used
*/

#include "header.h"

int main(int argc, char** argv){
	if (argc != 2){
		printf("Usage: <program> <disk_name>\n");
		return 1;
	}
	FILE* fd = open_disk(argv[argc-1]);
	struct BootSector *_bootSector = malloc(sizeof(struct BootSector));

	read_bootCode(fd, _bootSector); // Reading MBR Boot Code

	bool isfat32 = isFat32(count_clusters(_bootSector));
	printf("\nIs FAT32?\t\t%s\n", IS_FAT(isfat32));
	if (isfat32){
		test_mbr(_bootSector); // For testing purposes
		printf("\nFat Sector(s):\t\t%d\n", FATSEC_SIZE);
	}
	fclose(fd);
	return 0;
}
