/*
** EPITECH PROJECT, 2018
** my_put_str.c
** File description:
** Function that dislays one-by-one, characters of a string.
*/

#include "../../include/my.h"

int my_showstr(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        my_putchar(str[i]);
    }
    return (0);
}
