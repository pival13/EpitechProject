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

static int length_file(char *filepath)
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

char *load_file_in_mem(char *filepath)
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

void end_read_file(char *cnt, char **map)
{
    free(cnt);
    for (int i = 0; map[i] != NULL; i++) {
        if (map[i][0] == 0 || map[i][0] == '\n')
            map[i] = NULL;
    }
}

char **read_file(char *filepath)
{
    int length = length_file(filepath) + 1;
    char *cnt = load_file_in_mem(filepath);
    char **map = create_tab(length * 2);
    int x = 0;

    if (cnt == NULL)
        return (NULL);
    for (int i = 0; i <= length; map[i++] = create_string(my_strlen(cnt) * 2));
    for (int i = 0, j = 0; cnt[i] != 0; i++, j++) {
        while (cnt[i] == '\n') {
            i++;
            (map[x][0] != 0) ? (x++) : (0);
            j = 0;
        }
        if (cnt[i] == 0)
            break;
        map[x][j] = cnt[i];
    }
    end_read_file(cnt, map);
    return (map);
}
