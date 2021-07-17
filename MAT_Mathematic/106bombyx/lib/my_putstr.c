/*
** EPITECH PROJECT, 2018
** my_put_str.c
** File description:
** Function that dislays one-by-one, characters of a string.
*/

#include <unistd.h>
#include "../include/my.h"

int my_putstr(char *str)
{
    int nb = my_strlen(str);
    int i = 0;

    write(1, str, nb);
}
