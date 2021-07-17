/*
** EPITECH PROJECT, 2019
** my_putstr_error.c
** File description:
** my_putstr error
*/

#include "my.h"

void my_putstr_error(char *s)
{
    int len = my_strlen(s);

    write(2, s, len);
}
