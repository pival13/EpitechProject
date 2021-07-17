/*
** EPITECH PROJECT, 2018
** my_strncpy.c
** File description:
** Copy a string in an other string
*/

#include <stdlib.h>

char *my_strncpy(char const *src, int n)
{
    char *dest = malloc(sizeof(char) * (n + 1));
    int i = 0;

    if (dest == NULL)
        return (NULL);
    for (i = 0; src[i] != '\0' && i < n; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}
