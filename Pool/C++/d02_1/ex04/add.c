/*
** EPITECH PROJECT, 2020
** add.c
** File description:
** some additions functions
*/

#include "castmania.h"
#include <stdlib.h>

int normal_add(int a, int b)
{
    return a + b;
}

int absolute_add(int a, int b)
{
    return (a < 0 ? -a : a) + (b < 0 ? -b : b);
}

void exec_add(addition_t *ope)
{
    int (*f[2])(int, int) = { normal_add, absolute_add };

    if (ope == NULL || ope->add_type < 0 || ope->add_type > 2)
        return;
    ope->add_op.res = (*f[ope->add_type])(ope->add_op.a, ope->add_op.b);
}
