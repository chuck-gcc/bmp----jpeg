#include "bmp.h"

void to_hex(unsigned char *byte, int size)
{
    int i;
        
    i =  size - 1;
    printf("0x");
    while (i >= 0)
    {
        printf("%X",byte[i]);
        i--;
    }
    printf("\n");
}

void to_raw(unsigned char *byte, int size)
{
    int bit;
    int i;
        
    i =  size - 1;
    while (i >= 0)
    {
        if(size == 2)
            bit = 15;
        else
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

int to_binary(unsigned char *byte, int size)
{
    int bit, offset;
    int i;
    int value;
        
    i =  size - 1;
    if(size == 4)
        bit = 31;
    else
        bit = 15;
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
        bit--;
    }
    return(value);
}
