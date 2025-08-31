#include "bmp.h"

#define HEADER_SIZE 14

static int clean_bmp_object(t_bmp *bmp)
{
    free(bmp->header);
    free(bmp->info);
    free(bmp->data);
    free(bmp);

    return(0);
}

t_bmp *extract_bmp_data(const char *path)
{
    t_bmp           *bmp_data;

    bmp_data = malloc(sizeof(t_bmp));
    if(!bmp_data)
        return(NULL);
    bmp_data->header = get_header_object(path);
    if(!bmp_data->header)
    {
        printf("Error header\n");
        free(bmp_data);
        return(NULL);
    }
    bmp_data->info = get_info_header_object(path, HEADER_SIZE);
    if(!bmp_data->info)
    {
        printf("Error info\n");
        free(bmp_data->header);
        free(bmp_data);
        return(NULL);
    }
    bmp_data->data = get_image_data(bmp_data->header, bmp_data->info, path);
    if(!bmp_data->data)
    {
        printf("Error data\n");
        free(bmp_data->header);
        free(bmp_data->info);
        free(bmp_data);
        return(NULL);
    }
    bmp_data->clean = clean_bmp_object;
    return(bmp_data);
}