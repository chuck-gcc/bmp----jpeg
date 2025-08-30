#include "bmp.h"

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

int get_data_header(t_header *header,char *path)
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

t_header *get_header_object(void)
{
    t_header *header;

    header = malloc(sizeof(t_header));
    if(!header)
    {
        perror("Malloc err: ");
        return (NULL);
    }
    header->get_header = get_data_header;
    header->display_header = display_header;
    return(header);
}