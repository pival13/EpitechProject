/*
** EPITECH PROJECT, 2018
** infin_add.c
** File description:
** Function that add inf numbers.
*/

#include "../../include/my.h"
#include <stdlib.h>

int checkvalidity(char *nb1, char *nb2)
{
    int validity = 1;

    for (int i = 0; nb1[i] != 0; i++) {
        if (('0' > nb1[i] || '9' < nb1[i]) && nb1[i] != '+' && nb1[i] != '-')
            validity = 0;
    }
    for (int i = 0; nb2[i] != 0; i++) {
        if (('0' > nb2[i] || '9' < nb2[i]) && nb2[i] != '+' && nb2[i] != '-')
            validity = 0;
    }
    return (validity);
}

char *signe(char *number)
{
    char *numberfinal = malloc(sizeof(char)*(my_strlen(number) + 1));
    int j = 0;

    for (int i = 0; number[i] != 0; i++) {
        if (number[i] == '-' && j == 0) {
            j = 1;
        } else if (number[i] == '-' && j == 1) {
            j = 0;
        }
    }
    if (j == 1)
        numberfinal[0] = '-';
    for (int i = 0; number[i] != 0; i++) {
        if ('0' <= number[i] && number[i] <= '9') {
            numberfinal[j] = number[i];
            j++;
        }
    }
    return (numberfinal);
}

int optype(char *nb1, char *nb2)
{
    int op = 0;

    if (nb1[0] == '-')
        op++;
    if (nb2[0] == '-')
        op = op + 2;
    return (op);
}

char *operation(char *nb1, char *nb2, char *numberfinal, int opetype)
{
    int j = 0;
    int retenue = 0;
    int length = 0;
    if (opetype == 0 || opetype == 3)
        numberfinal = addition(nb1, nb2, numberfinal, opetype);
    else
        numberfinal = soustraction(nb1, nb2, numberfinal, opetype);
    return (numberfinal);
}

char *infin_add(char *nb1, char *nb2)
{
    int validity = 1;
    char *numberfinal;
    int operationtype = 0;

    validity = checkvalidity(nb1, nb2);
    if (validity == 0)
        exit(84);
    else {
        numberfinal = malloc(sizeof(char) * (my_strlen(nb1) + my_strlen(nb2)));
        nb1 = signe(nb1);
        nb2 = signe(nb2);
        operationtype = optype(nb1, nb2);
        numberfinal = operation(nb1, nb2, numberfinal, operationtype);
        return (numberfinal);
    }
}
