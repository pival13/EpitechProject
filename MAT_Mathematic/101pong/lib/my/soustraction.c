/*
** EPITECH PROJECT, 2018
** soustraction.c
** File description:
** For infin_add.c
*/

#include <stdlib.h>
#include "../../include/my.h"

int nbrlength(char *number1, char *number2)
{
    int length = 0;
    int test1 = my_strlen(number1);
    int test2 = my_strlen(number2);

    if (test1 >= test2)
        length = test1;
    else
        length = test2;
    return (length);
}

void compteurt1t2(sV *var)
{
    if (var->t2 == 0)
        var->nb2[0] = '0';
    if (var->t1 >= var->li)
        var->t1 = var->t1 - 1;
    if (var->t2 >= var->li)
        var->t2 = var->t2 - 1;
}

char *soustraction(char *number1, char *number2, char *numberfinal, int opetype)
{
    sV vars;

    vars.length = nbrlength(number1, number2);
    vars.t1 = my_strlen(number1) - 1;
    vars.t2 = my_strlen(number2) - 1;
    vars.li = 0;
    vars.nbf = numberfinal;
    vars.nb1 = number1;
    vars.nb2 = number2;
    vars.rtn = 0;
    if (opetype == 1)
        echangeopetype1(&vars);
    if (vars.t2 > vars.t1 + 1)
        vars.nbf[0] = '-';
    else if (vars.t2 == vars.t1 + 1)
        superior(&vars);
    if (vars.nbf[0] == '-')
        echangeminus(&vars);
    calculsoustraction(&vars);
    return (vars.nbf);
}
