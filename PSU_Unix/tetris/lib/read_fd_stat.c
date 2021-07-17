/*
** EPITECH PROJECT, 2019
** read_fd_stat.c
** File description:
** read a file with a file descriptor in a char *
*/

#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char *read_fd_stat(char *filepath)
{
    char *str;
    struct stat s;
    int fd = open(filepath, O_RDONLY);

    if (filepath == NULL || fd == -1)
        return (NULL);
    if (stat(filepath, &s) == -1)
        return (NULL);
    str = malloc(sizeof(char) * (s.st_size + 1));
    if (read(fd, str, s.st_size) != s.st_size)
        return (NULL);
    str[s.st_size] = '\0';
    close(fd);
    return (str);
}
