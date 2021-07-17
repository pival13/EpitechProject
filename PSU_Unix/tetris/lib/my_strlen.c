/*
** EPITECH PROJECT, 2018
** my_strlen
** File description:
** Return the length of a file
*/

#include <stdlib.h>

int my_arraylen(char **str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    for (; str[i] != NULL; i++);
    return (i);
}

int my_strlen(const char *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    for (; str[i] != '\0'; i++);
    return (i);
}
