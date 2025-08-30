#ifndef BMP_H
#define BMP_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#define TEST_START(f) printf("Start fonction: %s\n", f)

//header size 14 bytes
typedef struct s_header
{   
    unsigned char signature[2];
    unsigned char file_size[4];
    unsigned char reserved[4];
    unsigned char data_offset[4];
    int (*get_header)(struct s_header *head, char *path);
    void (*display_header)(struct s_header *header);
    
} t_header;

//header size 40 bytes

typedef struct s_Infoheader
{   
    unsigned char sizeIh[4]; // size of info header;
    unsigned char *width[4];
    unsigned char *height[4];
    unsigned char *planes[2];
    unsigned char *b_per_pixel[2];
    unsigned char *compression_type[4];
    unsigned char *image_size[4];
    unsigned char *XpixelsPerM[4];
    unsigned char *YpixelsPerM[4];
    unsigned char *color_used[4];
    unsigned char *imortant_colors[4];
    
} t_Infoheader;


t_header *get_header_object(void);

#endif