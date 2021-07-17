/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** main functions
*/

#include "my.h"
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int my_strlen_gnl(char *str)
{
    int i = 0;

    for (; str[i] != 0; i++);
    return (i);
}

char *my_stradd(char *dest, char *src)
{
    int i = 0;
    char *new;

    if (src[0] == 0)
        return (dest);
    new = malloc(sizeof(char) * (my_strlen_gnl(dest) + READ_SIZE + 2));
    if (new == NULL)
        return (NULL);
    for (i = 0; dest[i] != '\0'; i++)
        new[i] = dest[i];
    for (int j = 0; src[j] != '\0'; i++, j++) {
        new[i] = src[j];
        new[i+1] = 0;
    }
    return (new);
}

char *read_file1(int fd, char *cnt)
{
    char buf[READ_SIZE + 1];
    int error = 1;

    (cnt != NULL) ? (free(cnt)) : (0);
    cnt = malloc(sizeof(char));
    cnt[0] = 0;
    for (int i = 0; i < READ_SIZE; buf[i] = 0, i++);
    if (read(fd, buf, READ_SIZE) <= 0 || READ_SIZE == 0 || cnt == NULL)
        return (NULL);
    for (int t = 0; error != -1; read(fd, buf, READ_SIZE), error = 0, t++) {
        buf[READ_SIZE] = '\0';
        (buf[0] != 0) ? (cnt = my_stradd(cnt, buf)) : (0);
        for (int i = 0; i < READ_SIZE; buf[i] = 0, i++)
            (buf[i] == '\n' || buf[i] == 0) ? (error = -1) : (0);
        if (error == -1 && (cnt[0] >= 32 || (cnt[0] == 10 && cnt[1] == 0)))
            break;
        (cnt[0] == '\n') ? (cnt++) : (0);
    }
    return (cnt);
}

char *get_next_line2(char *line, char *cnt)
{
    int character = 0;

    line = malloc(sizeof(char) * (my_strlen_gnl(cnt) + 1));
    line[0] = 0;
    if (line == NULL)
        return (NULL);
    for (int i = character, j = 0; cnt[i] != '\0' && cnt[i] != '\n'; i++, j++) {
        line[j] = cnt[i];
        line[j+1] = '\0';
    }
    if (cnt[0] == '\n')
        line = "\n\0";
    return (line);
}

char *get_next_line(int fd)
{
    static char *cnt;
    static int fd_moment = -1;
    char *line = NULL;

    if (fd == -1)
        return (NULL);
    if (cnt == NULL || fd_moment == -1 || fd_moment != fd) {
        cnt = read_file1(fd, cnt);
        fd_moment = fd;
    }
    if (cnt == NULL)
        return (NULL);
    while (cnt[0] == '\n')
        cnt++;
    line = get_next_line2(line, cnt);
    for (; cnt[0] != '\n' && cnt[0] != 0; cnt++);
    (cnt[0] == '\n') ? (cnt++) : (0);
    (cnt[0] == 0 || fd == 0) ? (cnt = NULL) : (0);
    (line[0] == 0) ? (line = NULL) : (0);
    return (line);
}
