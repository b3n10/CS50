/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, but also resizes it, just because.
 * from: https://gist.githubusercontent.com/CraigRodrigues/8cf42cb785e4d6468ec201a5e0323069/raw/4e51895885bf90bafe82fd4bd609f2dad0c5c2da/resize.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
	// ensure proper usage
	if (argc != 4)
	{
		printf("Usage: ./resize factor infile outfile\n");
		return 1;
	}

	// remember filenames and resize factor
	int factor = atoi(argv[1]);
	char* infile = argv[2];
	char* outfile = argv[3];

	// check factor
	if (factor < 1 || factor > 100)
	{
		printf("Factor must be in the range [1-100]\n");
		return 1;
	}

	// open input file
	FILE* inptr = fopen(infile, "r");
	if (inptr == NULL)
	{
		printf("Could not open %s.\n", infile);
		return 2;
	}

	// open output file
	FILE* outptr = fopen(outfile, "w");
	if (outptr == NULL)
	{
		fclose(inptr);
		fprintf(stderr, "Could not create %s.\n", outfile);
		return 3;
	}

	// read infile's BITMAPFILEHEADER
	BITMAPFILEHEADER bf;
	BITMAPFILEHEADER bf_new;
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

	bf_new = bf;

	// read infile's BITMAPINFOHEADER
	BITMAPINFOHEADER bi;
	BITMAPINFOHEADER bi_new;
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

	bi_new = bi;

	// ensure infile is (likely) a 24-bit uncompressed BMP 4.0
	if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
			bi.biBitCount != 24 || bi.biCompression != 0)
	{
		fclose(outptr);
		fclose(inptr);
		fprintf(stderr, "Unsupported file format.\n");
		return 4;
	}

	// set new width and height dimensions
	bi_new.biWidth = bi.biWidth * factor;
	bi_new.biHeight = bi.biHeight * factor;

	// determine padding for scanlines
	int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	int new_padding =  (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

	// set new file size
	bf_new.bfSize = 54 + (bi_new.biWidth * sizeof(RGBTRIPLE) + new_padding) * abs(bi_new.biHeight);
	bi_new.biSizeImage = bf_new.bfSize - 54;

	fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);
	fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

	// iterate over infile's scanlines
	for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
	{
		// each row will be printed out factor times
		int rowcounter = 0;

		while (rowcounter < factor)
		{

			// iterate over pixels in scanline
			for (int j = 0; j < bi.biWidth; j++)
			{
				RGBTRIPLE triple;
				int pixelcounter = 0;
				fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
				while (pixelcounter < factor)
				{
					fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
					pixelcounter++;
				}
			}

			for (int k = 0; k < new_padding; k++)
				fputc(0x00, outptr);

			// seek back to the beginning of row in input file, but not after iteration of printing
			if (rowcounter < (factor - 1))
				fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
			rowcounter++;
		}
		fseek(inptr, padding, SEEK_CUR);
	}

	fclose(inptr);
	fclose(outptr);

	// that's all folks
	return 0;
}
