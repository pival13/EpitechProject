/*
** EPITECH PROJECT, 2019
** create_string.c
** File description:
** create string
*/

#include "my.h"

char *create_string(int size)
{
    char *str = malloc(sizeof(char) * (size + 1));

    if (str == NULL)
        return (NULL);
    for (int i = 0; i <= size; i++)
        str[i] = 0;
    return (str);
}
