#include "bmp.h"

void *clean_matrice_data(u_int8_t ***matrice, int x, int y, int stop)
{
    int i, j;

    i = 0;
    while (i < x)
    {
        j = 0;
        if(i == x - 1)
            y = stop;
        while (j < y)
        {
            if(matrice[i][j])
                free(matrice[i][j]);
            j++;
        }
        free(matrice[i]);
        i++;
    }
    free(matrice);
    return(NULL);
}

void    display_pixel_matrice(u_int8_t ***matrice,int x, int y)
{
    printf("R:%d G:%d B:%d\n", matrice[x][y][0], matrice[x][y][1], matrice[x][y][2]);
}

u_int8_t ***get_matrice_data(unsigned char *data, t_info_header *info)
{
    int i, j, k, l;
    int raw, col, depht;
    u_int8_t ***matrice;

    raw = to_binary(info->height, 4);
    col = to_binary(info->width, 4);
    depht = 3;

    i = 0;
    l = 0;

    matrice = malloc(sizeof(u_int8_t ***) * raw);
    if(!matrice)
        return(NULL);
    
    while (i < raw)
    {
        matrice[i] = malloc(sizeof(u_int8_t **) * col);
        
        /*
            error simulation memory check
            if(i == 100)
            {
                free(matrice[i]);
                matrice[i] = NULL;
            }
        */
        
        if(!matrice[i])
            return(clean_matrice_data(matrice,i ,col, col));
        j = 0;
        while (j < col)
        {
            
            k = 0;
            matrice[i][j] = malloc(sizeof(u_int8_t *) * depht);

            /*
            
                error simulation memory check
                if(i == 100 && j == 200)
                {
                    free(matrice[i][j]);
                    matrice[i][j] = NULL;
                }
            */
            
            if(!matrice[i][j])
            {
                return(clean_matrice_data(matrice,i + 1, col, j));
            }
            while (k < depht)
            {
                matrice[i][j][k] = data[l];
                l++;
                k++;
            }
            j++;
        }
        i++;
    }
    assert(l == to_binary(info->image_size, 4));
    return(matrice);
}

unsigned char *get_image_data(t_header *header, t_info_header *info, const char *path)
{
    int fd, img_size, offset, b_read;
    unsigned char *data;

    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        perror("Err get image data:");
        return(NULL);
    }
    offset = to_binary(header->data_offset, 4);
    img_size = to_binary(info->image_size, 4);

    data = malloc(img_size * sizeof(unsigned char));
    if(!data)
    {
        perror("malloc:");
        return(NULL);
    }
    
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