#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		fprintf(stderr, "Usage: resize f infile outfile\n");
		return 1;
	}

	// 1st arg is float input, 2nd is infile, 3rd is outfile
	float f = atof(argv[1]);
	char *infile = argv[2];
	char *outfile = argv[3];

	FILE *inptr = fopen(infile, "r");
	if (inptr == NULL)
	{
		fprintf(stderr, "Could not open %s.\n", infile);
		return 2;
	}

	FILE *outptr = fopen(outfile, "w");
	if (outptr == NULL)
	{
		fclose(inptr);
		fprintf(stderr, "Could not create %s.\n", outfile);
		return 3;
	}

	// read infile's BITMAPFILEHEADER and BITMAPINFOHEADER
	BITMAPFILEHEADER bf;
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
	BITMAPINFOHEADER bi;
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

	// change biWidth and biHeight by factor of f
	float biWidthF = bi.biWidth * f;
	float biHeightF = bi.biHeight * f;
	printf("biWidthF: %f\nbiHeightF: %f\n", biWidthF, biHeightF);

	// ensure infile is (likely) a 24-bit uncompressed BMP 4.0
	if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
	{
		fclose(outptr);
		fclose(inptr);
		fprintf(stderr, "Unsupported file format.\n");
		return 4;
	}

	// determine padding for scanlines
	int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

	// resize biSizeImage and bfSize
	bi.biSizeImage = ((sizeof(RGBTRIPLE) * biWidthF) + padding) * fabsf(biHeightF * f);
	bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	/*
	// write outfile's BITMAPFILEHEADER and BITMAPINFOHEADER
	fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
	fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

	// iterate over infile's scanlines
	for (int i = 0, biHeight = abs(bi.biHeight * f); i < biHeight; i++)
	{
		// iterate over pixels in scanline
		for (int j = 0; j < biWidthF; j++)
		{
			// temporary storage
			RGBTRIPLE triple;

			// read RGB triple from infile
			fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

			// write RGB triple to outfile
			fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
		}

		// skip over padding, if any
		fseek(inptr, padding, SEEK_CUR);

		// then add it back (to demonstrate how)
		for (int k = 0; k < padding; k++)
		{
			fputc(0x00, outptr);
		}
	}
	*/

	fclose(inptr);
	fclose(outptr);

	return 0;
}
