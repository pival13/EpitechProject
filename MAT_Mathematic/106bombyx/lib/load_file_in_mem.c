/*
** EPITECH PROJECT, 2018
** load_file_in_mem.c
** File description:
** bstrap
*/

#include "my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

char *load_file_in_mem(char const *filepath)
{
    struct stat *statbuff = malloc(sizeof(struct stat));
    int size = 0;
    char *buffer = 0;
    int fd;

    stat(filepath, statbuff);
    size = statbuff->st_size;
    buffer = malloc(size);
    fd = open(filepath, O_RDONLY);
    if (read(fd, buffer, size) == (-1))
        exit(84);
    for (int i = size; buffer[i+1] != 0; i++)
        buffer[i] = 0;
    free(statbuff);
    close(fd);
    return (buffer);
}
