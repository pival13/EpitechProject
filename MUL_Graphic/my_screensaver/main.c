/*
** EPITECH PROJECT, 2018
** main
** File description:
** Prepare the screensaver
*/

#include "my.h"
#include "csfml.h"

int main2(int);

int main(int n, char **arg)
{
    int a = 0;

    if (n != 2) {
        my_printf(NB_ARG, arg[0], n-1);
        return (84);
    }
    if (my_strcmp(arg[1], "-h") == 0) {
        my_printf(USAGE, NB_SS);
        return (0);
    } else if (my_strcmp(arg[1], "-d") == 0) {
        my_printf(DESCRIPTION);
        return (0);
    }
    a = my_getnbr(arg[1]);
    if (my_str_isnum(arg[1]) == 0 || a < 1 || a > NB_SS) {
        my_printf(TYPE_ARG, arg[0], NB_SS);
        return (84);
    }
    main2(a);
}
