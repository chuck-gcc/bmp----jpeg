

#define BMP_HEADER_SIZE 14
#define SIGNATURE 2
#define FILE_SIZE 4
#define RESERVED 4
#define OFFSET 4

#include "bmp/bmp.h"

void to_binary(unsigned char *byte, int size)
{
    int bit;
    int i;
    i =  size - 1;
    while (i >= 0)
    {
        bit = 7;
        while (bit >= 0)
        {
            int c = byte[i] >> bit & 1;
            printf("%d", c);
            bit--;
        }

        i--;
    }
    printf("\n");

}


int test(void)
{
    int bit =  7;
    int v = 0;

    while (bit >= 0)
    {
        v  =  100 >> bit;
        bit--;
    }
    printf("final: %d\n", v );

    return(0);
}

int main(void)
{

    t_header *header;
    
    header = get_header_object();
    if(!header)
        return(-1);
    if((header->get_header(header,"imaget.bmp")) != 0)
    {
        free(header);
        return(1);
    }
    to_binary(header->file_size, FILE_SIZE);

    free(header);
    return(0);

}