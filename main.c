#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#define BMP_HEADER_SIZE 14
#define SIGNATURE 0
#define FILE_SIZE 2
#define RESERVED 6
#define OFFSET 10

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

typedef struct s_bmp_image
{
    t_header        header;

} t_bmp_image;


int get_header(t_header *header,char *path)
{
    int fd;
    int b_read_1, b_read_2, b_read_3, b_read_4;

    fd = open(path,O_RDONLY);
    if(fd == -1)
    {
        perror("err:");
        return(1);
    }

    b_read_1 = read(fd,header->signature,2);
    if(b_read_1  == -1)
    {
        perror("Err signature:");
        return(errno);
    }
    b_read_2 = read(fd,header->file_size,4);
    if(b_read_2  == -1)
    {
        perror("Err file size:");
        return(errno);
    }
    b_read_3 =  read(fd,header->reserved,4);
    if(b_read_3  == -1)
    {
        perror("Err reserved:");
        return(errno);
    }
    b_read_4 = read(fd,header->data_offset,4);
    if(b_read_4  == -1)
    {
        perror("Err offset header:");
        return(errno);
    }
    return(0);
}

void display_header(t_header *head)
{
    TEST_START("display header");
    int i;
    unsigned char *h[4];

    i = 0;

    h[0] = head->signature;
    h[1] = head->file_size;
    h[2] = head->reserved;
    h[3] = head->data_offset;

    while (i < 4)
    {
        int j = 0;
        int size;
        if(i == 0)
            size = 2;
        else
            size = 4;

        if(i == 0)
            printf("\nsignature: ");
        else if(i == 1)
            printf("\nFile size: ");
        else if(i == 2)
            printf("\nReserved: ");
        else if(i == 3)
            printf("\nOffset: ");
            
        while (j < size)
        {
            printf("%d ",h[i][j]);
            j++;
        }
        i++;
    }
    printf("\n");
}

int main(void)
{

    t_header *header;

    header = malloc(sizeof(t_header));
    if(!header)
    {
        perror("Malloc err: ");
        return (1);
    }
    header->get_header = get_header;
    header->display_header = display_header;
    header->get_header(header,"imaget.bmp");
    header->display_header(header);
    return(0);

}