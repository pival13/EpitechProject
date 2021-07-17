/*
** EPITECH PROJECT, 2018
** soustraction2.c
** File description:
** for soustraction.c
*/

#include <stdlib.h>
#include "../../include/my.h"

void echangeopetype1(sV *var)
{
    char *echange = malloc(sizeof(var->nb2));

    echange = var->nb2;
    var->nb2 = var->nb1;
    var->nb1 = echange;
    var->t1 = my_strlen(var->nb1) - 1;
    var->t2 = my_strlen(var->nb2) - 1;
}

void echangeminus(sV *var)
{
    char *echange = malloc(sizeof(var->nb2));

    var->li = 1;
    echange = var->nb2;
    var->nb2 = var->nb1;
    var->nb1 = echange;
    var->t1 = my_strlen(var->nb1) - 1;
    var->t2 = my_strlen(var->nb2) - 1;
}

void superior(sV *var)
{
    int sup = 0;
    int j = 1;

    for (int i = 0; var->nb1[i] != 0 && var->nb2[j] != 0 && sup == 0; i++) {
        if (var->nb2[j] < var->nb1[i]) {
            sup = 1;
        } else if (var->nb2[j] > var->nb1[i]) {
            var->nbf[0] = '-';
            sup = 1;
        }
        j++;
    }
}

void rewriteminus(sV *var)
{
    char stock = 0;
    char stockbefore = 0;
    char *final = malloc(sizeof(var->nbf));
    int length = my_strlen(var->nbf);

    if (var->nbf[0] == '-') {
        final[0] = '-';
        for (int i = var->length - 1; i >= 1; i--) {
            stock = var->nbf[i];
            final[i] = stockbefore;
            stockbefore = stock;
        }
    } else {
        for (int i = var->length - 1; i >= 0; i--) {
            stock = var->nbf[i];
            final[i] = stockbefore;
            stockbefore = stock;
        }
    }
    var->nbf = final;
}

void calculsoustraction(sV *var)
{
    int li = var->li;

    for (int i = var->length - 1; i >= var->li; i--) {
        var->nbf[i] = var->nb1[var->t1] - var->nb2[var->t2] + 48 - var->rtn;
        var->rtn = 0;
        if (var->nb1[var->t1] < ('0' - 9) || var->nb1[var->t1] > '9')
            var->nbf[i] = var->nbf[i] + var->nb1[var->t1] - 48;
        if (var->nb2[var->t2] < '0' || var->nb2[var->t2] > '9')
            var->nbf[i] = var->nbf[i] + var->nb2[var->t2] - 48;
        if (var->nbf[i] < 0)
            var->nbf[i] = 0;
        if (var->nbf[i] < 48) {
            var->rtn = 1;
            var->nbf[i] += 10;
        }
        compteurt1t2(var);
    }
    while (var->nbf[li] <= 48 && var->nbf[li] != 45 && var->nbf[li+1] != 0)
        rewriteminus(var);
}
