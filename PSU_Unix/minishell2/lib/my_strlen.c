/*
** EPITECH PROJECT, 2018
** my_strlen.c
** File description:
** Display the longer of a string
*/

#include <stdlib.h>

int my_strlen(char const *str)
{
    int	n = 0;

    if (str == NULL)
        return (0);
    for (;str[n] != '\0'; n++);
    return (n);
}
