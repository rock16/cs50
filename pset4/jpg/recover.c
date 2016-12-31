/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
 
typedef uint8_t BYTE;
 
int main(void)
{
    //open memory card
    FILE* memcard = fopen("card.raw", "rb");
    if (memcard == NULL)
    {
        printf("File not found");
        return 1;
    }
    
    //create a space on the heap for jpg filename.
    char* title = malloc(sizeof(char) * 7);
    if (title == NULL)
    {
        fclose(memcard);
        free(title);
        printf("Memory error");
        return 2;
    }
    else
    {
        // determine if a jpg file found is written or not.
        bool write = false, start = false;
        int filename = 0;
        
        // initialize buffer.
        BYTE cluster[512];
        FILE* newfile;
        
        // read file onto buffer from input or memorycard.
        while (fread(&cluster, sizeof(char), 512, memcard) > 0)
        {
            
            // check for the begining of a jpg file.
            if (cluster[0] == 0xff && cluster[1] == 0xd8 && cluster[2] == 0xff)
            {
                // create a file name for each jpg found.
                sprintf(title, "%03d.jpg", filename);
                write = true;
                
                // create the first jpg file.
                if (write && !start)
                {
                    newfile = fopen(title, "wb");
                }
                
                // close the previous jpg file and create a new file.
                else if (write && start)
                {
                    fclose(newfile);
                    newfile = fopen(title, "wb");
                }
                filename++;
            }
            
            // write from buffer to output.
            if (write)
            {
                fwrite(&cluster, 1, 512, newfile);
                start = true;
            }
        }
        
        // close all open files.
        fclose(memcard);
        if (write)
        {
            fclose(newfile);
        }
        free(title);
    }
}