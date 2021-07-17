/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** main of the 101pong project
*/

#include "include/my.h"

int pong(float x0, float y0, float z0, float x1, float y1, float z1, int n);

int main(int ac, char **av)
{
    if (ac != 8) {
        my_putstr("Please enter the xyz-coordinates of the two vector's \
extremities and a time shift.\n");
        return (84);
    }
    if (my_str_isnum(av[1]) + my_str_isnum(av[2]) + my_str_isnum(av[3]) + my_str_isnum(av[4]) + my_str_isnum(av[5]) + my_str_isnum(av[6]) + my_str_isnum(av[7]) != 7) {
        my_putstr("Please enter only numbers.\n");
        return (84);
	}
    pong(my_getfloat(av[1]), my_getfloat(av[2]), my_getfloat(av[3]), \
         my_getfloat(av[4]), my_getfloat(av[5]), my_getfloat(av[6]), my_getnbr(av[7]));
    return (0);
}
