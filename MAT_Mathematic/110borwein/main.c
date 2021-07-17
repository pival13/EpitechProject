/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main 110borwein
*/

#include "my.h"

#define PI 3.1415926535897932384626433

int error_arg(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (84);
    }
    return (0);
}

int main(int ac, char **av)
{
    double nb = 0;
    double nb_str = 0;
    double gap = 0;

    if (help_option(av) == 1)
        return (0);
    if (ac != 2)
        return (84);
    if (error_arg(av[1]) == 84)
        return (84);
    nb = atof(av[1]);
    nb_str = nb;
    nb = integration_midpoint(calcul_func, 0, 5000, nb_str);
    printf("Midpoint:\nI%g = %.10f\ndiff = %.10f\n", nb_str, nb, (PI / 2) - nb);
    nb = integration_trapez(calcul_func, 0, 5000, nb_str);
    printf("\nTrapezoidal:\nI%g = %.10f\ndiff = %.10f\n", nb_str, nb, (PI / 2) - nb);
    nb = integration_simpson(calcul_func, 0, 5000, nb_str);
    printf("\nSimpson:\nI%g = %.10f\ndiff = %.10f\n", nb_str, nb, (PI / 2) - nb);
}
