/*
** EPITECH PROJECT, 2020
** log_config.c
** File description:
** log config
*/

#include "log.h"

enum log_level set_log_level(enum log_level change)
{
    static enum log_level lv = ERROR;

    if (change > 0 && change < 5)
        lv = change;
    return lv;
}

enum log_level get_log_level(void)
{
    return set_log_level(-1);
}

int log_file(int new_fd)
{
    static int fd = 2;

    if (new_fd != -1)
        fd = new_fd;
    return fd;
}

int close_log_file(void)
{
    int c = 0;

    if (log_file(-1) == 2)
        return 0;
    c = close(log_file(-1));
    if (c == -1)
        return 1;
    log_file(2);
    return 0;
}

int set_log_file(const char *filename)
{
    int fd = 0;

    if (filename == NULL)
        return 1;
    if (log_file(-1) != -1)
        close_log_file();
    fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (fd == -1)
        return 1;
    log_file(fd);
    return 0;
}
