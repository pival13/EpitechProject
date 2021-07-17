/*
** EPITECH PROJECT, 2019
** read_file
** File description:
** read a file with GNL
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

char *get_next_line(int fd);

int length_file(char *filepath)
{
    char *line;
    int fd = open(filepath, O_RDONLY);
    int i = 0;

    if (filepath == NULL)
        fd = 0;
    else if (fd == -1) return (0);
    line = get_next_line(fd);
    for (; line != NULL; i++) {
        free(line);
        line = get_next_line(fd);
    }
    if (fd != 0) close(fd);
    return (i);
}

char **read_file(char *filepath)
{
    int length = length_file(filepath) + 1;
    int fd = open(filepath, O_RDONLY);
    char **map;

    if (fd == -1) {
        my_dprintf(2, "Not existing file\n");
        return (NULL);
    } else if (filepath == NULL)
        fd = 0;
    map = malloc(sizeof(char *) * length);
    if (map == NULL)
        return (NULL);
    for (int i = 0; 1; i++) {
        map[i] = get_next_line(fd);
        if (map[i] == NULL) break;
    }
    if (map[0] == NULL)
        my_dprintf(2, "Empty file\n");
    close(fd);
    return (map);
}
