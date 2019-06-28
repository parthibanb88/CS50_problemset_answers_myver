#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    
    if (file == NULL)
    {
        printf("Usage: ./resize f infile outfile\n");
        return 2;
    }

    unsigned char buffer[512];
    int count = 0;
    
    do
    {
        fread(buffer, 1, 512, file);
    }
    while (buffer[0] != 0xff && buffer[1] != 0xd8 && buffer[2] != 0xff && (buffer[3] & 0xf0) != 0xe0);
    
    
    char filename[8];
    sprintf(filename, "%03i.jpg", count);
    FILE *img = fopen(filename, "w+");
    count += 1;
    fwrite(buffer, 1, 512, img);
    
    while (fread(buffer, 1, 512, file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            fclose(img);
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w+");
            count += 1;
            fwrite(buffer, 1, 512, img);
        }
        
        else
        {
            fwrite(buffer, 1, 512, img);
        }
        
    }
    
    fclose(img);
    fclose(file);
}
