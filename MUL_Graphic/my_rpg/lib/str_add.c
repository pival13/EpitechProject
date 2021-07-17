/*
** EPITECH PROJECT, 2019
** str_add.c
** File description:
** str add
*/

#include "my.h"

char *str_add(char *base, char *toadd)
{
    char *new;
    int i = 0;

    if (base == NULL && toadd == NULL)
        return (NULL);
    if (base == NULL)
        return (my_strcpy(toadd));
    if (toadd == NULL)
        return (my_strcpy(base));
    new = malloc(sizeof(char) * (my_strlen(base) + my_strlen(toadd) + 1));
    for (; base[i] != '\0'; i++)
        new[i] = base[i];
    for (int j = 0; toadd[j] != '\0'; j++, i++)
        new[i] = toadd[j];
    new[i] = '\0';
    return (new);
}
