/*
** EPITECH PROJECT, 2019
** cmp_color
** File description:
** say if two color are same
*/

#include "my.h"
#include "my_world.h"

int cmp_color(sfColor c1, sfColor c2)
{
    if (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a)
        return 1;
    return 0;
}
