#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
	// if incorrect usage
	if (argc != 4)
	{
		fprintf(stderr, "Usage: resize f infile outfile\n");
		return 1;
	}

	int f = atoi(argv[1]); // parse to float
	char *infile = argv[2];
	char *outfile = argv[3];

	FILE *inptr = fopen(infile, "r");
	if (inptr == NULL)
	{
		fprintf(stderr, "Error on %s file!\n", infile);
		return 2;
	}

	FILE *outptr = fopen(outfile, "w");
	if (outptr == NULL)
	{
		fprintf(stderr, "Error on %s file!\n", outfile);
		return 3;
	}

	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

	// read file and info header from input file
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

	// resize biWidth and biHeight by factor of f
	// float f_biWidth = bi.biWidth * f;
	// float f_biHeight = bi.biHeight * f;

	int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

	// bi.biSizeImage is total size of image (pixels + padding)
	bi.biSizeImage = ((sizeof(RGBTRIPLE) * (bi.biWidth * f)) + padding) * abs(bi.biHeight * f);
	// bf.bfSize is total size of file (pixels, padding and headers)
	bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// write file and info header to output file
	fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
	fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


	/*
	printf("%i\n", bi.biHeight);
	printf("%i\n", bi.biWidth);
	  resizing horizontally:
	  for each row
	  	for each pixel in row
	  		write to outfile n times
	  	write outfile's padding
	  	skip over infile's padding
	 */
	for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
	{
		for (int j = 0; j < bi.biWidth; j++)
		{
			RGBTRIPLE triple;
			fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
			for (int k = 0; k < f; k++)
			{
				fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
			}
		}
		for (int k = 0; k < padding; k++)
		{
			fputc(0x00, outptr);
		}
		fseek(inptr, padding, SEEK_CUR);
	}
	/*
	  	resizing vertically
	  	1
	  	for each row
	  		write to array n times
	  	for n times
	  		write array to outfile
	  		write outfile padding
	  	skip over infile padding
			*/
	for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
	{
		RGBTRIPLE triple;
		fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
		for (int k = 0, ff = f - 1; k < ff; k++)
		{
			fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
			fputc(0x00, outptr);
			fseek(inptr, padding, SEEK_CUR);
		}
		fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
		fputc(0x00, outptr);
		fseek(inptr, padding, SEEK_CUR);
	}
	/*
	  	2
	  	for each row
	  		for n-1 times
	  			write pixels, padding to outfile
	  			send infile cursor back
	  		write pixels, padding to outfile
	  		skip over infile padding
	 */


	fclose(inptr);
	fclose(outptr);
	// upon success
	return 0;
}
