/*
** EPITECH PROJECT, 2018
** infin_sub.c
** File description:
** To substract between numbers.
*/

#include "../../include/my.h"
#include <stdlib.h>

char *infin_sub(char *nb1, char *nb2)
{
    char *nb2mod = malloc(sizeof(char) * sizeof(nb2) + sizeof(char) * 2);
    int i = 1;

    nb2mod[0] = '-';
    for (; nb2[i-1] != 0; i++) {
        nb2mod[i] = nb2[i-1];
    }
    nb2mod[i] = 0;
    nb1 = infin_add(nb1, nb2mod);
    return (nb1);
}
