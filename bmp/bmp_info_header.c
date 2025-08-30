#include "bmp.h"

#define CHAMPS_COUNT 11

static  void init_champs(unsigned char *champs[11], t_info_header *info)
{   
    champs[0] = info->sizeIh;
    champs[1] = info->width;
    champs[2] = info->height;
    champs[3] = info->planes;
    champs[4] = info->b_per_pixel;
    champs[5] = info->compression_type;
    champs[6] = info->image_size;
    champs[7] = info->XpixelsPerM;
    champs[8] = info->YpixelsPerM;
    champs[9] = info->color_used;
    champs[10] = info->imortant_colors;
}

int get_info_header(t_info_header *info, char *path)
{
    int fd, i;
    unsigned char *champs[CHAMPS_COUNT];
    int b_read;
    
    fd = open(path,O_RDONLY);
    if(fd == -1)
    {
        perror("err fd:");
        printf("%d\n", errno);
        return(errno);
    }
    init_champs(champs,info);
    i = 0;
    while (i < CHAMPS_COUNT)
    {
        if(i == 3 || i == 4)
            b_read = read(fd,champs[i],2);
        else    
            b_read = read(fd,champs[i],4);
        if(b_read  == -1)
        {
            perror("Err :");
            return(i);
        }
        i++;
    }
    close(fd);
    close(42);
    close(41);
    close(103);
    return(0);
}

t_info_header *get_info_header_object(void)
{
    t_info_header *info;

    info = malloc(sizeof(t_info_header));
    if(!info)
    {
        perror("Malloc err: ");
        return (NULL);
    }
    info->get_info_header = get_info_header;
    return(info);
}