/*
** EPITECH PROJECT, 2019
** my_strcpy.c
** File description:
** my strcpy
*/

#include "my.h"

char *my_strcpy(char *str)
{
    char *new = NULL;

    if (str == NULL || str[0] == 0)
        return (NULL);
    new = malloc(sizeof(char) * (my_strlen(str) + 1));
    if (new == NULL)
        return (NULL);
    for (int i = 0; str[i] != 0; i++) {
        new[i] = str[i];
        new[i+1] = '\0';
    }
    return (new);
}
