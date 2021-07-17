/*
** EPITECH PROJECT, 2018
** str_add.c
** File description:
** str_add
*/

#include "my.h"
#include <stdlib.h>

char *str_add(char *base, char *toadd)
{
    char *new = malloc(sizeof(char) * (my_strlen(base) + my_strlen(toadd)));
    int i = 0;

    for (; base[i] != 0; i++)
        new[i] = base[i];
    for (int j = 0; toadd[j] != 0; j++, i++) {
        new[i] = toadd[j];
    }
    new[i] = 0;
    return (new);
}
