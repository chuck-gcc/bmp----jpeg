#include "bmp.h"

unsigned char *get_image_data(t_header *header, t_info_header *info, char *path)
{
    int fd, img_size, offset, b_read;

    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        perror("Err get image data:");
        return(NULL);
    }
    offset = to_binary(header->data_offset, 4);
    img_size = to_binary(info->image_size, 4);

    
    assert(img_size == 873180);
    assert(offset == 54);

    if(lseek(fd,offset, SEEK_SET) == -1)
    {
        perror("lseek error\n");
        return(NULL);
    }
    b_read = read(fd, data, img_size);
    if(b_read == -1)
    {
        perror("Read error:");
        return(NULL);
    }
        
    return(data);
} 