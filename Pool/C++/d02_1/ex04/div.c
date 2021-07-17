/*
** EPITECH PROJECT, 2020
** div.c
** File description:
** some functions related to div
*/

#include "castmania.h"
#include <stdlib.h>

int integer_div(int a, int b)
{
    if (b == 0)
        return 0;
    return (a/b);
}

float decimale_div(int a, int b)
{
    if (b == 0)
        return 0;
    return (float)a/(float)b;
}

void exec_div(division_t *ope)
{
    decimale_op_t *dope;
    integer_op_t *iope;

    if (ope == NULL)
        return;
    if (ope->div_type == INTEGER) {
        iope = ope->div_op;
        iope->res = integer_div(iope->a, iope->b);
    } else if (ope->div_type == DECIMALE) {
        dope = ope->div_op;
        dope->res = decimale_div(dope->a, dope->b);
    }
}