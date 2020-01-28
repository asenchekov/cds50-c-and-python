#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

// aliases for C/C++ primitive data types
// https://msdn.microsoft.com/en-us/library/cc230309.aspx
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

// information about the type, size, and layout of a file
// https://msdn.microsoft.com/en-us/library/dd183374(v=vs.85).aspx
typedef struct
{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} __attribute__((__packed__))
BITMAPFILEHEADER;

// information about the dimensions and color format
// https://msdn.microsoft.com/en-us/library/dd183376(v=vs.85).aspx
typedef struct
{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} __attribute__((__packed__))
BITMAPINFOHEADER;

// relative intensities of red, green, and blue
// https://msdn.microsoft.com/en-us/library/dd162939(v=vs.85).aspx
typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover infile\n");
        return 1;
    }

    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");

    //Checks if file can be oppened
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // Declaring variables
    BYTE buffer[512];
    int fileCount = 0;
    bool newJPG = false;
    FILE *newImage;

    // while loop which will run through the file and stop when EOF.
    while (fread(buffer, 1, 512, inptr))
    {
        // Checks if buffer is header of an image
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            //checks if we have already writing on an image
            if (!newJPG)
            {
                newJPG = true;
                char filename[8];
                sprintf(filename, "%03i.jpg", fileCount++);
                newImage = fopen(filename, "w");

                if (newImage == NULL)
                {
                    return 3;
                }

                fwrite(buffer, 1, 512, newImage);
            }
            else
            {
                fclose(newImage);
                char filename[8];
                sprintf(filename, "%03i.jpg", fileCount++);
                newImage = fopen(filename, "w");

                if (newImage == NULL)
                {
                    return 3;
                }

                fwrite(buffer, 1, 512, newImage);
            }
        }
        else
        {
            if (newJPG)
            {
                fwrite(buffer, 1, 512, newImage);
            }
        }
    }

    fclose(newImage);
    fclose(inptr);
    exit(EXIT_SUCCESS);
}