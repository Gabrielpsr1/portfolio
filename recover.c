#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    int file_count = 0;
    char filename[20];
    FILE *img;
    // open the memory card file
    FILE *card = fopen("card.raw", "r");
    // repeat until end of the file
    // read 512 bytes into a buffer
    uint8_t buffer[512];
    while (fread(buffer, sizeof(uint8_t), 512, card) == 512)
    {
        // if it starts a jpeg
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) &&
            ((buffer[3] & 0xf0) == 0xe0))
        {
            // if it is the first jpeg 001...
            if (file_count == 0)
            {
                sprintf(filename,"%03i.jpeg", file_count + 1);
                img =fopen(filename,"w");
                fwrite(buffer,sizeof(uint8_t),512,img);
                file_count++;
            }
            // else close the file,open the new file
            else
            {
                fclose(img);
                file_count++;
                sprintf(filename,"%03i.jpeg", file_count + 1);
                img = fopen(filename, "w");
                fwrite(buffer,sizeof(uint8_t),512,img);
            }
        }
        // else vontinue to read the file
        else
        {
            fwrite(buffer,sizeof(uint8_t),512,img);
        }
    }
    // close
    fclose(img);
}
