

#define BMP_HEADER_SIZE 14
#define SIGNATURE 2
#define FILE_SIZE 4
#define RESERVED 4
#define OFFSET 4

#include "bmp/bmp.h"
#include  "libft/libft.h"

void write_data(char *path)
{
    int fd;
    int b_read;
    unsigned char b[1];
    int i;

    if((fd = open(path, O_RDONLY))== -1)
    {
        perror("err write data: ");
        return;
    }
    i = 0;
    while ((b_read = read(fd, b, 1)) > 0)
    {
       printf("%d ", b[0]);
        if(i == 15)
        {
            printf("\n");
            i = 0;
        }
        i++;
    }
     
}

int get_raw_data(unsigned char *data, t_info_header *info)
{

    int i = 0;
    int off = 0;
    int fd;
    char *value;

    fd = open("image/raw_data", (O_CREAT | O_WRONLY), 0777);
    if(fd == -1)
    {
        perror("Err raw data:");
        return(errno);
    }

    while (i < to_binary(info->image_size, 4))
    {
        value = ft_itoa((int)data[i]);
        write(fd, value, ft_strlen(value));
        write(fd, " ", 1);
        // if() == -1)
        // {
        //     perror("Err raw data writing:");
        //     free(value);
        //     return(errno);
        // }
        free(value);
        off++;
        if(off == to_binary(info->width, 4) * 3)
        {
            off = 0;
            write(fd, "\n", 1);
        }
        i++;
    }
    close(fd);
    return(0);
}

int main(int argc, char **argv)
{

    t_header        *header;
    t_info_header   *info;
    

    if(argc < 2)
    {
        printf("Error set thr path: export IMG_PATH= your image path\n");
        return(1);
    }
    
    header = get_header_object();
    if(!header)
        return(-1);
    if((header->get_header(header,argv[1])) != 0)
    {
        free(header);
        return(1);
    }
    header->display_header(header);
    info = get_info_header_object();
    if(!info)
        return(1);
    info->get_info_header(info,argv[1], 14);


    assert(to_binary(info->height, 4) == 441);
    assert(to_binary(info->width, 4) == 660);

    // info->display_header_info(info);
    // info->display_raw_header_info(info);
    // info->display_hex_header_info(info);
    unsigned char *data =  get_image_data(header, info, argv[1]);
    get_raw_data(data, info);

    free(data);
    free(header);
    free(info);
    return(0);

}