

#define BMP_HEADER_SIZE 14
#define SIGNATURE 2
#define FILE_SIZE 4
#define RESERVED 4
#define OFFSET 4

#include "bmp/bmp.h"

int to_binary(unsigned char *byte, int size)
{
    int bit, offset;
    int i;
    int value;
        
    
    i =  size - 1;
    while (i >= 0)
    {
        bit = 31;
        offset = 7;
        value = 0;
        while (bit >= 0)
        {
            int c = byte[i] >> offset & 1;
            if(c == 1)
                value =  value | (1 << bit);
            offset--;
            if(offset < 0)
            {
                offset = 7;
                i--;
            }
            printf("%d", c);
            bit--;
        }

    }
    printf("\n");
    return(value);
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
    int size_file = to_binary(header->file_size, FILE_SIZE);
    int off = to_binary(header->data_offset, OFFSET);
    printf("File size: %d Kb\n", size_file);
    printf("header offset: %d Kb\n", off);
    free(header);
    return(0);

}