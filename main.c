

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


// int get_matrice_data(unsigned char *data, t_info_header *info)
// {
//     int i, j, k, l;
//     int raw, col, depht;

//     raw = to_binary(info->height, 4);
//     col = to_binary(info->width, 4);
//     depht = 3;

//     u_int8_t matrice[raw][col][depht];
//     i = 0;
//     l = 0;
//     while (i < raw)
//     {
//         j = 0;
//         while (j < col)
//         {
//             k = 0;
//             // printf("ligne %d\n", i);
//             // printf("Colone %d\n", j);
//             while (k < depht)
//             {
//                 matrice[i][j][k] = data[l];
//                 //printf("\tvalue %d\n", matrice[i][j][k]);
//                 l++;
//                 k++;
//             }
//             j++;
//         }
//         i++;
//     }
//     (void)matrice;
//     assert(l == to_binary(info->image_size, 4));
//     return(0);
// }


int clean_matrice_data(u_int8_t ***matrice, int x, int y);

int main(int argc, char **argv)
{

    t_bmp *bmp;

    
    if(argc < 2)
    {
        printf("Error set thr path: export IMG_PATH= your image path\n");
        return(1);
    }
    bmp = extract_bmp_data(argv[1]);
    if(!bmp)
        return(1);


    u_int8_t ***matrice = get_matrice_data(bmp->data, bmp->info);
    if(!matrice)
    {
        bmp->clean(bmp);
        return(1);
    }
    
    clean_matrice_data(matrice, 441, 660);
    bmp->clean(bmp);
    return(0);

}