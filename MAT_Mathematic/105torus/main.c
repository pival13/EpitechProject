/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of 105torus
*/

#include <stdlib.h>
#include "my.h"

void bissection(double coeff[5], int accur, double x, double y, int depth);

void newton(double coeff[5], int accur, double x, int depth);

void secant(double coeff[5], int accur, double x, double y, int depth);

int main(int n, char **arg)
{
    double coeff[5];

    if (n != 8 || my_str_isint(arg[1]) == 0 || my_str_isint(arg[7]) == 0)
        return (84);
    for (int i = 2; i != 7; i++)
        if (my_str_isfloat(arg[i]) == 0)
            return (84);
    if (atoi(arg[1]) > 3 || atoi(arg[1]) < 1 || atoi(arg[7]) < 0)
        return (84);
    for (int i = 0; i != 5; i++)
        coeff[i] = strtod(arg[2+i], NULL);
    if (atoi(arg[1]) == 1)
        bissection(coeff, atoi(arg[7]), 0, 1, 1);
    else if (atoi(arg[1]) == 2)
        newton(coeff, atoi(arg[7]), 0.5, 1);
    else
        secant(coeff, atof(arg[7]), 0, 1, 1);
}
