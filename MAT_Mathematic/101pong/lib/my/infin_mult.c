/*
** EPITECH PROJECT, 2018
** infin_add.c
** File description:
** Function that add inf numbers.
*/

#include <stdlib.h>
#include "../../include/my.h"

int checkvaliditymult(char *nb1, char *nb2)
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

char *signemult(char *number)
{
    char *numberfinal = malloc(sizeof(number) + 1);
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

int optypemult(char *nb1, char *nb2)
{
    int op = 0;

    if (nb1[0] == '-')
        op++;
    if (nb2[0] == '-')
        op = op + 2;
    return (op);
}

char *operationmult(char *nb1, char *nb2, char *numberfinal, int opetype)
{
    int j = 0;

    if (nb1[0] == '0' || nb2[0] == '0')
        return ("0");
    numberfinal = multiplication(nb1, nb2, opetype);
    if (opetype == 0 || opetype == 3);
    else
        numberfinal = addminus(numberfinal);
    return (numberfinal);
}

char *infin_mult(char *nb1, char *nb2)
{
    int validity = 1;
    char *numberfinal = malloc(sizeof(nb1) + sizeof(nb2));
    int operationtype = 0;

    validity = checkvaliditymult(nb1, nb2);
    if (validity == 0)
        exit(84);
    else {
        nb1 = signemult(nb1);
        nb2 = signemult(nb2);
        operationtype = optypemult(nb1, nb2);
        nb1 = removeminus(nb1);
        nb2 = removeminus(nb2);
        numberfinal = operationmult(nb1, nb2, numberfinal, operationtype);
        return (numberfinal);
    }
}
