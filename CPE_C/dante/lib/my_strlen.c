/*
** EPITECH PROJECT, 2018
** my_strlen.c
** File description:
** return length
*/

#include <stdlib.h>

int my_strlen(char *str)
{
    int i = 0;

    if (str == NULL) return (0);
    for (; str[i] != '\0' && str[i] != '\n'; i++);
    return (i);
}
