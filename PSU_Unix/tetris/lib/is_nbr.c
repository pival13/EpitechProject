/*
** EPITECH PROJECT, 2019
** is_nbr.c
** File description:
** is_nbr.c
*/

#include "my.h"

int is_nbr(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (0);
    }
    return (1);
}
