/*
** EPITECH PROJECT, 2018
** my_strcpy.c
** File description:
** Copy a string in an other string
*/

#include <stdlib.h>

unsigned char *my_strcpy(unsigned char const *src)
{
    int i = 0;
    unsigned char *dest;

    for (; src[i] != '\0'; i++);
    dest = malloc(sizeof(unsigned char) * (i + 1));
    if (dest == NULL)
        return (NULL);
    if (dest == NULL)
        return (NULL);
    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}

char *my_strcpy_not_unsigned(char const *src)
{
    int i = 0;
    char *dest = NULL;

    if (!src)
        return (NULL);
    for (; src[i] != '\0'; i++);
    dest = malloc(sizeof(char) * (i + 1));
    if (dest == NULL)
        return (NULL);
    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}