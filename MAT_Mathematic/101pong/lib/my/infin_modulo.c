/*
** EPITECH PROJECT, 2018
** infin_modulo.c
** File description:
** modulo
*/

#include "../../include/my.h"

char *modulonominus(char *nb)
{
    char *newnb = malloc(sizeof(nb));

    for (int i = 1; nb[i] != 0; i++)
        newnb[i-1] = nb[i];
    return (newnb);
}

char *infin_modulo(char *nb1, char *nb2)
{
    char *step1 = malloc(sizeof(nb1));
    char *step2 = malloc(sizeof(nb1));
    char *result = malloc(sizeof(nb1));

    if (nb1[0] == '-')
        nb1 = modulonominus(nb1);
    if (nb2[0] == '-')
        nb2 = modulonominus(nb2);
    step1 = infin_div(nb1, nb2);
    step2 = infin_mult(step1, nb2);
    result = infin_sub(nb1, step2);
    return (result);
}
