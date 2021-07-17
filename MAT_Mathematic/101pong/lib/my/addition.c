/*
** EPITECH PROJECT, 2018
** addition.c
** File description:
** calcul addition
*/

#include "../../include/my.h"

char *rewrite(char *nbf)
{
    char stock = '0';
    char stockbefore = '1';
    int i = 0;

    if (nbf[0] == '-')
        i = 1;
    for (; stockbefore != 0; i++) {
        stock = nbf[i];
        nbf[i] = stockbefore;
        stockbefore = stock;
    }
    return (nbf);
}

void calcul_addition(var_add *addV)
{
    int rtn = 0;

    for (int i = addV->length - 1; i >= addV->limit; i--) {
        addV->nbf[i] = addV->nb1[addV->t1-1] + addV->nb2[addV->t2-1] + rtn - 48;
        rtn = 0;
        if (addV->nb1[addV->t1-1] < '0' || addV->nb1[addV->t1-1] > '9')
            addV->nbf[i] = addV->nbf[i] - addV->nb1[addV->t1-1] + 48;
        if (addV->nb2[addV->t2-1] < '0' || addV->nb2[addV->t2-1] > '9')
            addV->nbf[i] = addV->nbf[i] - addV->nb2[addV->t2-1] + 48;
        if (addV->nbf[i] > 57) {
            rtn = 1;
            addV->nbf[i] -= 10;
        }
        if (rtn == 1 && i == addV->limit)
            addV->nbf = rewrite(addV->nbf);
        if (addV->t1 != addV->limit)
            addV->t1 = addV->t1 - 1;
        if (addV->t2 != addV->limit)
            addV->t2 = addV->t2 - 1;
    }
}

char *addition(char *nb1, char *nb2, char *nbf, int opetype)
{
    int rtn = 0;
    int length = nbrlength(nb1, nb2);
    int t1 = my_strlen(nb1);
    int t2 = my_strlen(nb2);
    int limit = 0;
    var_add addV;

    if (opetype == 3) {
        nbf[0] = '-';
        limit = 1;
    }
    addV.length = length;
    addV.t1 = t1;
    addV.t2 = t2;
    addV.limit = limit;
    addV.nbf = nbf;
    addV.nb1 = nb1;
    addV.nb2 = nb2;
    calcul_addition(&addV);
    return (addV.nbf);
}
