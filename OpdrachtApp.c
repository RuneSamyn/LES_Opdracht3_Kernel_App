#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
 
#include "OpdrachtKernelModule.h"
 
void get_edges(int fd)
{
    query_arg_t q;
 
    if (ioctl(fd, GET_EDGES, &q) == -1)
    {
        perror("OpdrachtKM get edges");
    }
    else
    {
        printf("Number of edges : %d\n", q.edges);
    }
}
void clear_edges(int fd)
{
    if (ioctl(fd, CLEAR_EDGES) == -1)
    {
        perror("OpdrachtKM clear edges");
    }
}
void set_toggle_speed(int fd)
{
    int speed;
    query_arg_t q;
 
    printf("Enter Toggle Speed: ");
    scanf("%d", &speed);
    getchar();
    q.toggleSpeed = speed;
 
    if (ioctl(fd, SET_TOGGLE_SPEED, &q) == -1)
    {
        perror("query_apps ioctl set");
    }
}
 
int main(int argc, char *argv[])
{
    char *file_name = "/dev/opdrachtKM";
    int fd;
    enum
    {
        e_get,
        e_clr,
        e_set
    } option;
 
    if (argc == 1)
    {
        option = e_get;
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "-g") == 0)
        {
            option = e_get;
        }
        else if (strcmp(argv[1], "-c") == 0)
        {
            option = e_clr;
        }
        else if (strcmp(argv[1], "-s") == 0)
        {
            option = e_set;
        }
        else
        {
            fprintf(stderr, "Usage: %s [-g | -c | -s]\n", argv[0]);
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "Usage: %s [-g | -c | -s]\n", argv[0]);
        return 1;
    }
    fd = open(file_name, O_RDWR);
    if (fd == -1)
    {
        perror("OpdrachtKM open");
        return 2;
    }
 
    switch (option)
    {
        case e_get:
            get_edges(fd);
            break;
        case e_clr:
            clear_edges(fd);
            break;
        case e_set:
            set_toggle_speed(fd);
            break;
        default:
            break;
    }
 
    close (fd);
 
    return 0;
}
