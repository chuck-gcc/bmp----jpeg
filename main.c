

#define BMP_HEADER_SIZE 14
#define SIGNATURE 2
#define FILE_SIZE 4
#define RESERVED 4
#define OFFSET 4

#include "bmp/bmp.h"




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

    t_header        *header;
    t_info_header   *info;
    
    header = get_header_object();
    if(!header)
        return(-1);
    if((header->get_header(header,"imaget.bmp")) != 0)
    {
        free(header);
        return(1);
    }
    header->display_header(header);
    free(header);

    info = get_info_header_object();
    if(!info)
        return(1);

    info->get_info_header(info,"imaget.bmp");
    free(info);
    return(0);

}