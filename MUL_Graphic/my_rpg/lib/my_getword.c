/*
** EPITECH PROJECT, 2018
** my_getnbr.c
** File description:
** Convert a str number into an int
*/

#include <stdlib.h>

char *my_getword(char const *str)
{
    int len = 0;
    char *cpy;

    for (; str && str[len] != '\0' && str[len] != ','; len++);
    cpy = malloc(sizeof(char) * (len+1));
    for (int i = 0; i != len; i++)
        cpy[i] = str[i];
    cpy[len] = '\0';
    return (cpy);
}
