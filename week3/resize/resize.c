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

	float f = atof(argv[1]); // parse to float
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


	// upon success
	return 0;
}
