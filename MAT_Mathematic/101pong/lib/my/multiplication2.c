/*
** EPITECH PROJECT, 2018
** multiplication2.c
** File description:
** To complete multiplication.c
*/

#include "../../include/my.h"

char *multiplication2(char nb1, char *nb2)
{
    char *resultat = malloc(sizeof(char) * (sizeof(nb2) + 10));
    int compteur = 0;
    int i = 0;

    compteur = nb1 - 48;
    for (; compteur > 0; compteur--) {
        resultat = infin_add(resultat, nb2);
    }
    return (resultat);
}

char *addzero(char *toadd, int digitplus)
{
    int n = 0;

    for (; toadd[n] != 0; n++);
    for (; digitplus > 0; digitplus--, n++) {
        toadd[n] = '0';
    }
    toadd[n] = 0;
    return (toadd);
}
