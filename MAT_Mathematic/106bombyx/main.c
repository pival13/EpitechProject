/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of 106bombyx
*/

#include <math.h>
#include <stdlib.h>
#include "my.h"

int main(int n, char **arg)
{
    if (n != 3 && n != 4) return (84);
    if (is_int(arg[1]) == 0 || atoi(arg[1]) < 0) return (84);
    if (n == 3 && (is_float(arg[2]) == 0 || atof(arg[2]) < 1 || atof(arg[2]) > 4)) return (84);
    if (n == 4 && (is_int(arg[2]) == 0 || is_int(arg[3]) == 0 || atoi(arg[2]) >= atoi(arg[3]) || atoi(arg[2]) < 0)) return (84);
    if (n == 3) calcul_bombyx_2arg(atoi(arg[1]), atof(arg[2]));
    if (n == 4) calcul_bombyx_3arg(atoi(arg[1]), atoi(arg[2]), atoi(arg[3]));
}
