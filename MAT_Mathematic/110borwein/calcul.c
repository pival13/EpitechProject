/*
** EPITECH PROJECT, 2019
** calcul.c
** File description:
** calcul func
*/

#include "my.h"

double calcul_func(double x, double n)
{
    double res = sin(x)/x;
    double num = 0;
    double denom = 0;

    if (x == 0)
        res = 1;
    for (int k = 1; k <= n; k++) {
        num = sin(x / (2 * k + 1));
        denom = x / (2 * k + 1);
        res *= num / denom;
    }
    return (res);
}
