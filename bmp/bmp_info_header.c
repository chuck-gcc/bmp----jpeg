#include "bmp.h"

#define CHAMPS_COUNT 11

int to_binary(unsigned char *byte, int size);
void to_raw(unsigned char *byte, int size);

void display_header_info(t_info_header *info)
{
    TEST_START("display header info\n");
    printf("Size info header: %d kb\n", to_binary(info->sizeIh, 4));
    printf("Image width: %d px\n", to_binary(info->width, 4));
    printf("Image height: %d px\n", to_binary(info->height, 4));
    printf("Plane: %d kb\n", to_binary(info->planes, 2));
    printf("B_per_pixel: %d kb\n", to_binary(info->b_per_pixel, 2));
    printf("Compression type: %d kb\n", to_binary(info->compression_type, 4));
    printf("Image size: %d kb\n", to_binary(info->image_size, 4));
    printf("XpixelsPerM: %d kb\n", to_binary(info->XpixelsPerM, 4));
    printf("YpixelsPerM: %d kb\n", to_binary(info->YpixelsPerM, 4));
    printf("Color used: %d kb\n", to_binary(info->color_used, 4));
    printf("Color: %d kb\n", to_binary(info->imortant_colors, 4));
    printf("\n");
}

void display_raw_header_info(t_info_header *info)
{
    TEST_START("display  raw header info\n");
    printf("Size info header:");
    to_raw(info->sizeIh, 4);
    printf("Image width: ");
    to_raw(info->width, 4);
    printf("Image height: ");
    to_raw(info->height, 4);
    printf("Plane: ");
    to_raw(info->planes, 2);
    printf("B_per_pixel:");
    to_raw(info->b_per_pixel, 2);
    printf("Compression type: ");
    to_raw(info->compression_type, 4);
    printf("Image size:");
    to_raw(info->image_size, 4);
    printf("XpixelsPerM:");
    to_raw(info->XpixelsPerM, 4);
    printf("YpixelsPerM");
    to_raw(info->YpixelsPerM, 4);
    printf("Color used");
    to_raw(info->color_used, 4);
    printf("Color:");
    to_raw(info->imortant_colors, 4);
    printf("\n");
}

void display_hex_header_info(t_info_header *info)
{
    TEST_START("display  raw header info\n");
    printf("Size info header:");
    to_hex(info->sizeIh, 4);
    printf("Image width: ");
    to_hex(info->width, 4);
    printf("Image height: ");
    to_hex(info->height, 4);
    printf("Plane: ");
    to_hex(info->planes, 2);
    printf("B_per_pixel: ");
    to_hex(info->b_per_pixel, 2);
    printf("Compression type: ");
    to_hex(info->compression_type, 4);
    printf("Image size: ");
    to_hex(info->image_size, 4);
    printf("XpixelsPerM: ");
    to_hex(info->XpixelsPerM, 4);
    printf("YpixelsPerM: ");
    to_hex(info->YpixelsPerM, 4);
    printf("Color used: ");
    to_hex(info->color_used, 4);
    printf("Color: ");
    to_hex(info->imortant_colors, 4);
    printf("\n");
}

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

int get_info_header(t_info_header *info, char *path, int offset)
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
    if(lseek(fd,offset, SEEK_SET) == -1)
    {
        perror("lseek error\n");
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
    info->display_header_info = display_header_info;
    info->display_raw_header_info = display_raw_header_info;
    info->display_hex_header_info = display_hex_header_info;
    return(info);
}