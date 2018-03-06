#include <stdio.h>
#include <stdlib.h>
// to store buffer as byte(uint8_t) data type
#include <stdint.h>
// for bool
#include <stdbool.h>

// define custom data type
typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: ./recover card.raw\n");
		return 1;
	}

	FILE *inptr = fopen(argv[1], "r");
	if (inptr == NULL)
	{
		fprintf(stderr, "Cannot open %s\n", argv[1]);
		return 2;
	}

	int bf = 512, count = 0;
	BYTE buffer[512];
	char filename[8];
	bool current_jpg = false;
	FILE *outptr = NULL;

	while (bf == 512)
	{
		// read 512 bytes of data
		bf = fread(buffer, 1, 512, inptr);
		// check if bytes on buffer has signature for new jpg
		if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
		{
			// if there is a currently opened file
			if (current_jpg)
			{
				// close current file
				fclose(outptr);
				// increase count for filename
				count++;
			}
			// create filename
			sprintf(filename, "%03i.jpg", count);
			// open filename and set to write mode
			outptr = fopen(filename, "w");
			// flag for current file
			current_jpg = true;
		}
		// write on current filename
		if (current_jpg)
		{
			// use bf instead of 512, so it will write 0 to outptr if fread returns 0 once EOF is detected
			// from https://cs50.stackexchange.com/a/19189
			fwrite(buffer, 1, bf, outptr);
		}
	}

	// upon success
	fclose(inptr);
	return 0;
}