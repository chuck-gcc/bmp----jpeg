#include "bmp.h"

int to_binary(unsigned char *byte, int size)
{
    int bit, offset;
    int i;
    int value;
        
    
    i =  size - 1;
    while (i >= 0)
    {
        bit = 31;
        offset = 7;
        value = 0;
        while (bit >= 0)
        {
            int c = byte[i] >> offset & 1;
            if(c == 1)
                value =  value | (1 << bit);
            offset--;
            if(offset < 0)
            {
                offset = 7;
                i--;
            }
            //printf("%d", c);
            bit--;
        }

    }
    printf("\n");
    return(value);
}

void display_header(t_header *head)
{
    TEST_START("display header\n");
    printf("File size: %c%c", head->signature[0],head->signature[1]);
    printf("File size: %d kb", to_binary(head->file_size,4));
    printf("Offset Data: %d kb", to_binary(head->data_offset, 4));
    printf("\n");
}


int get_data_header(t_header *header,char *path)
{
    int fd, i;
    unsigned char *champs[4];
    int b_read;


    fd = open(path,O_RDONLY);
    if(fd == -1)
    {
        perror("err fd:");
        printf("%d\n", errno);
        return(errno);
    }
    champs[0] = header->signature;
    champs[1] = header->file_size;
    champs[2] = header->reserved;
    champs[3] = header->data_offset;
    i = 0;
    while (i < 4)
    {
        if(i == 0)
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