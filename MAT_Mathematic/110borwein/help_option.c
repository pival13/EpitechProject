/*
** EPITECH PROJECT, 2019
** help_option.c
** File description:
** help option
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "my.h"

char *load_file_in_mem(char const *filepath)
{
    struct stat *statbuff = malloc(sizeof(struct stat));
    int size = 0;
    char *buffer = 0;
    int fd;

    stat(filepath, statbuff);
    size = statbuff->st_size;
    buffer = malloc(sizeof(char) * (size + 1));
    fd = open(filepath, O_RDONLY);
    if (read(fd, buffer, size) == (-1))
        return (NULL);
    buffer[size] = 0;
    free(statbuff);
    close(fd);
    return (buffer);
}

int help_option(char **av)
{
    int ac = 0;
    char *str;

    for (ac = 0; av[ac] != NULL; ac++);
    if (ac != 2)
        return (0);
    if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == 0) {
        str = load_file_in_mem("./help_message");
        printf("%s", str);
        return (1);
    }
    return (84);
}
