/*
** EPITECH PROJECT, 2018
** my_put_str.c
** File description:
** Function that dislays one-by-one, characters of a string.
*/

#include "../../include/my.h"

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i = i + 1;
    }
}
