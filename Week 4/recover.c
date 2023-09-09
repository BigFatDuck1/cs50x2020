#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover FILENAME\n");
        return 1;
    }

    char* filename = argv[1];
    if (filename == NULL)
    {
        printf("Please type the correct file name!\n");
        return 2;
    }

    //Open "card.raw", the pointer is stored in variable "image"
    FILE *image = fopen(filename,"r");

    //Create array for a block of 512 bytes
    unsigned char fixed_512[512];
    unsigned char store_512[512];
    int image_count = 0;
    char image_name[8];
    int x = 1;
    //When fread() returns a value less than 512, means it has reached EOF, break out of while{}
    while (x == 1)
    {
        //Read 512 bytes and store it in fixed_512[]
        int fread_value = fread(fixed_512,1,512,image);

        if (fread_value != 512)
        {
            //EOF reached
            break;
        }

        //Check if the first three bytes of the block contains 0xff, 0xd8, 0xff
        if (fixed_512[0] == 0xff && fixed_512[1] == 0xd8 && fixed_512[2] == 0xff)
        {
            /*Check with bitwise operator: if either one is 0, returns 0, and since 0xf0 is zero,
            the last half-byte always returns 0 */
            //If first half-byte is zero, zero is returned, if it is 1, both F and 1 is 1, 1 is returned
            if ((fixed_512[3] & 0xf0) == 0xe0)
            {
                //Check pass, it is a jpeg
                sprintf(image_name,"%03i.jpg",image_count);
                FILE *new_jpeg = fopen(image_name,"a");

                fwrite(fixed_512, 1, 512, new_jpeg);

                //Get next block and see it is a jpg
                int on_jpg = 1;
                while (on_jpg == 1) 
                {
                    fread_value = fread(fixed_512,1,512,image);

                    if (fread_value != 512)
                    {
                        //EOF reached
                        x = 0;
                        break;
                    }

                    if (fixed_512[0] == 0xff && fixed_512[1] == 0xd8 && fixed_512[2] == 0xff && ((fixed_512[3] & 0xf0) == 0xe0))
                    {
                        //New jpeg found
                        image_count += 1;
                        fseek(image, -512, SEEK_CUR);
                        fclose(new_jpeg);
                        break;
                    }
                    else
                    {
                        fwrite(fixed_512, 1, 512, new_jpeg);
                    }
                }
            }
            else 
            {
                //Check failed, not a jpg
                continue;
            }
        }
    }







    //Close file
    fclose(image);
}
