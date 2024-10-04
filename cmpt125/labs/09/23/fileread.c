#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char *fname;
	FILE *file;
	if (argc >= 1) {
		*fname = *argv[0];

		if (access(fname, F_OK) == 0) {
			file = fopen(fname, "r");
		} else {
			printf("Given file \"%s\" doesn't exist. Exiting.\n", fname);
		}

	} else {
		return EXIT_FAILURE;
	}

	long fsize = fseek(file, 0, SEEK_END);

	char *data = malloc(fsize * sizeof(char));

	fread(data, fsize, fsize, file);

	for (int i = 0; i < fsize; i++) {
		char byte = data[i];
		/*
		char b0 = (data[i] & 0b00000011) >> 0;
		char b1 = (data[i] & 0b00001100) >> 2;
		char b2 = (data[i] & 0b00110000) >> 4;
		char b3 = (data[i] & 0b11000000) >> 6;
		*/

		for (int j = 0; j < 4; j++) {
			switch (byte & 0x03) {
			case 0x00:
				puts(".");
				break;
			case 0x01:
				puts("*");
				break;
			case 0x02:
				puts("%");
				break;
			case 0x03:
				puts("#");
				break;
			}
			byte = byte >> 2;
		}

		if (i % 8 == 0) {
			puts("\n");
		}
	}

	free(data);

	return EXIT_SUCCESS;
}
