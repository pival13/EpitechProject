/*
** EPITECH PROJECT, 2018
** my_strdup.c
** File description:
** Copy a string into a malloc string
*/

#include <stdlib.h>

int my_strlen(char const *str)
{
    int	n = 0;

    if (str == NULL || *str == '\0')
        return (0);
    for (; str[n] != '\0'; n++);
    return (n);
}

char *my_strdup(char const *src)
{
    char *str = malloc(sizeof(char) * (my_strlen(src)+1));
    int i = 0;

    if (str == NULL)
        return (NULL);
    for (; src[i] != '\0'; i++)
        str[i] = src[i];
    str[i] = '\0';
    return (str);
}
