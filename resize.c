// seek method. after reading a line, cursor position is changed for factor-1 times


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize f infile outfile\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if ((argv[1][i]) < 48 || (argv[1][i] > 57))
        {
            printf("Usage: ./resize f infile outfile\n");
            return 1;
        }
    }

    int factor = 0;
    for (int i = strlen(argv[1]) - 1, j = 1; i >= 0; i--)
    {
        factor = factor + (argv[1][i] - 48) * j;
        j = j * 10;
    }
    printf("factor %i", factor);

    if (factor < 1 || factor > 100)
    {
        printf("Number should be between 1 and 100\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

        // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }



    // chnage width and height of output image
    int width_of_small = bi.biWidth;
    int width_of_large = factor * bi.biWidth;
    bi.biWidth = width_of_large;
    int height_of_small = abs(bi.biHeight);
    bi.biHeight = -(factor * height_of_small);
    int height_of_large = height_of_small * factor;
    printf("width of small %i\n", width_of_small);
    printf("width of large %i\n", width_of_large);
    printf("height of small %i\n", height_of_small);
    printf("height of large %i\n", height_of_large);

    // determine padding for input image
    int padding_infile = ((4 - (3*width_of_small) % 4) % 4);
    printf("padding infile %i\n", padding_infile);

    // determine padding for output image
    int padding_outfile = ((4 - (3*width_of_large) % 4) % 4);
    printf("padding outfile %i\n", padding_outfile);

    // determine size of image part
    int size_of_large = (bi.biWidth*3 + padding_outfile) * height_of_large;
    printf("size of large %i", size_of_large);
    bi.biSizeImage = size_of_large;

    // determine total size of image
    bf.bfSize = size_of_large + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < height_of_small; i++)
    {
        for (int z = 0; z < factor - 1; z++)

        {
            for (int j = 0; j < width_of_small; j++)
            {

                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int k = 0; k < factor; k++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                }
            }

            // then add it back (to demonstrate how)
            for (int l = 0; l < padding_outfile; l++)
            {
                fputc(0x00, outptr);
            }

            fseek(inptr, -(3 * width_of_small), SEEK_CUR);
        }
        for (int j = 0; j < width_of_small; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int k = 0; k < factor; k++)
            {
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

            }
        }

        // then add it back (to demonstrate how)
        for (int l = 0; l < padding_outfile; l++)
        {
            fputc(0x00, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding_infile, SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
