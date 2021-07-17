/*
** EPITECH PROJECT, 2019
** my_writer.c
** File description:
** Created by etienne-miltgen,
*/

#include "my.h"

int my_writer(int fd, char *str, int size)
{
    int i = 0;
    i = write(fd, str, size);
    if (i == -1)
        return (84);
    return (0);
}