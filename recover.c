#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    int file_count = 0;
    char filename[20];
    FILE *img;
    uint8_t *buffer = malloc(512 * sizeof(uint8_t));
    // open the memory card file
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        fclose(card);
        return 2;
    }
    // repeat until end of the file
    // read 512 bytes into a buffer
    while (fread(buffer, sizeof(uint8_t), 512, card) == 512)
    {
        // if it starts a jpeg
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) &&
            ((buffer[3] & 0xf0) == 0xe0))
        {
            // if it is the first jpeg 001...
            if (file_count == 0)
            {
                sprintf(filename, "%03i.jpg", file_count);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    fclose(img);
                    return 2;
                }
                fwrite(buffer, sizeof(uint8_t), 512, img);
                file_count++;
            }
            // else close the file,open the new file
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", file_count);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    fclose(img);
                    return 2;
                }
                fwrite(buffer, sizeof(uint8_t), 512, img);
                file_count++;
            }
        }
        // else continue to read the file
        else if (file_count > 0)
        {
            fwrite(buffer, sizeof(uint8_t), 512, img);
        }
    }
    // close
    fclose(img);
    fclose(card);
    free(buffer);
    return 0;
}
