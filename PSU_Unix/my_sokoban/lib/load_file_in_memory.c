/*
** EPITECH PROJECT, 2018
** load_file_in_memory
** File description:
** copy the file in memory
*/

#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

char *load_file_in_memory(char const *filepath)
{
    struct stat *statbuff = malloc(sizeof(struct stat));
    char *str;
    int fd = 0;
    int nb_read = 0;

    (statbuff == NULL) ? exit(84) : statbuff;
    fd = open(filepath, fd, O_RDONLY);
    (fd == -1) ? exit(84) : fd;
    stat(filepath, statbuff);
    str = malloc(sizeof(char) * statbuff->st_size + 1);
    (str == NULL) ? (exit(84)) : (str);
    nb_read = read(fd, str, statbuff->st_size);
    str[statbuff->st_size] = '\0';
    close(fd);
    free(statbuff);
    if (nb_read == -1)
        exit(84);
    else
        return (str);
}
