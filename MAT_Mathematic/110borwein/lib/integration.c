/*
** EPITECH PROJECT, 2019
** integration.c
** File description:
** integration
*/

#include <math.h>
#include "my.h"

double integration_midpoint(double (*funct)(double, double), double min, double max, double n)
{
    double nb = 0;

    for (int i = 0; i != 10000; i++)
        nb += (*funct)(min+(i*(max-min)/10000)+(0.5*(max-min)/10000), n);
    return ((max-min)/(10000)*nb);
}

double integration_trapez(double (*funct)(double, double), double min, double max, double n)
{
    double nb = 0;

    for (int i = 1; i != 10000; i++)
        nb += (*funct)(min+i*(max-min)/10000, n);
    return ((max - min) / (2 * 10000) * (1 + (*funct)(max, n) + 2*nb));
}

double integration_simpson(double (*funct)(double, double), double min, double max, double n)
{
    double nb = 0;
    double nb2 = 0;

    for (int i = 1; i != 10000; i++)
        nb += (*funct)(min + i*(max-min)/10000, n);
    for (int i = 0; i != 10000; i++)
        nb2 += (*funct)(min + i*(max-min)/10000 + (max-min)/20000, n);
    return ((max-min)/(6*10000)*(1 + (*funct)(max, n) + 2*nb + 4*nb2));
}
