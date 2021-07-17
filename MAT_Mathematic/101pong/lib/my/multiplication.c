/*
** EPITECH PROJECT, 2018
** multiplication.c
** File description:
** For multiplication.
*/

#include "../../include/my.h"

char *multiplication(char *nb1, char *nb2, int opetype)
{
    char *numberfinal = malloc(sizeof(nb1) * sizeof(nb2));
    int digitplus = -1;
    int n1 = 0;
    char *toadd = malloc(sizeof(char) * (sizeof(nb1) * sizeof(nb2))+5);

    for (; nb1[n1] != 0; n1++);
    for (; n1 >= 0; digitplus++, n1--) {
        toadd = multiplication2(nb1[n1], nb2);
        toadd = addzero(toadd, digitplus);
        numberfinal = infin_add(numberfinal, toadd);
    }
    free(toadd);
    return (numberfinal);
}

char *removeminus(char *nb)
{
    char *newnb = nb;
    int j = 0;

    if (nb[0] == '-') {
        newnb = malloc(sizeof(char) * sizeof(nb));
        for (int i = 1; nb[i] != 0; i++, j++)
            newnb[j] = nb[i];
    }
    return (newnb);
}

char *addminus(char *nb)
{
    char *newnb;
    int j = 0;

    newnb = malloc(sizeof(char) * sizeof(nb) + 10);
    newnb[0] = '-';
    for (int i = 1; nb[j] != 0; i++, j++)
        newnb[i] = nb[j];
    return (newnb);
}
