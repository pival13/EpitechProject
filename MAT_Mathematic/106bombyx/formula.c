/*
** EPITECH PROJECT, 2019
** formula.c
** File description:
** formula funcs
*/

#include "my.h"

void calcul_bombyx_2arg(int n, double k)
{
    double un;
    double un1;

    for (int step = 1; step <= 100; step++) {
        if (step == 1) {
            un1 = (double)(n);
        } else {
            un = un1;
            un1 = k * un * ((1000 - un) / 1000);
            if (un1 < 0)
                un1 = 0;
        }
        printf("%d %.2f\n", step, un1);
    }
}

void calcul_bombyx_3arg(int n, const int geni, const int genf)
{
    float result;

    for (double k = 1.00; k < 4.00; k += 0.01) {
        result = n;
        for (int i = 1; i <= genf; i++) {
            if (i >= geni)
                printf("%.2f %.2f\n", k, result);
            result = k * result * ((1000 - result) / 1000);
        }
    }
}
