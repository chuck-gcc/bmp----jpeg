

#define BMP_HEADER_SIZE 14
#define SIGNATURE 0
#define FILE_SIZE 2
#define RESERVED 6
#define OFFSET 10

#include "bmp/bmp.h"


int main(void)
{

    t_header *header;
    
    header = get_header_object();
    if(!header)
        return(-1);

    header->get_header(header,"imaget.bmp");
    header->display_header(header);
    return(0);

}