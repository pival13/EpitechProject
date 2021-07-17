/*
** EPITECH PROJECT, 2019
** funct_rational
** File description:
** funct rational
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"

double funct_polynome(double x, double *coeff, int size)
{
    double result = coeff[size-1];

    for (int i = 0; i != size-1; i++)
        result = x*result + coeff[size-2-i];
    return (result);
}

double funct_rational(double x, double **coeff, int *size)
{
    double f;
    int j = 0;
    double result;

    for (; size[j] != 0; j++);
    f = funct_polynome(x, coeff[j-1], size[j-1]);
    for (int i = 0; i != j-1; i++) {
        result = coeff[j-2-i][size[j-2-i]-1]/f;
        for (int k = 0; k != size[j-2-i] - 1; k++) {
            result = x*result + (coeff[j-2-i][size[j-2-i]-2-k])/f;
        }
        f = result;
    }
    return (f);
}

double **av_to_vars(int ac, char **av)
{
    double **vars = malloc(sizeof(double *) * (ac + 1));

    for (int i = 0; i <= ac; i++)
        vars[i] = NULL;
    for (int i = 1; i < ac; i++)
        vars[i-1] = numbers_per_line(av[i]);
    return (vars);
}

int main(int ac, char **av)
{
    double f;
    double **vars;
    int *size;
    
    if (ac % 2 == 0 || error_management(ac, av) == 84)
        return (84);
    vars = av_to_vars(ac, av);
    size = measure_vars(vars);
    for (double x = 0; x < 1.001; x += 0.001) {
        f = funct_rational(x, vars, size);
        if (isnan(f) == 1)
            f = 0.00000000;
        printf("%.*lf -> %.*lf\n", 3, x, 5, f);
    }
    return (0);
}
