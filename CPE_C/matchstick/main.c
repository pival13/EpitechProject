/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of matchstick
*/

#include "my.h"
#include <stdlib.h>
#include <unistd.h>
#include "matchstick.h"

int main(int n, char **arg)
{
    match_t map;

    if (n != 3 || my_getnbr(arg[2]) <= 0 || my_getnbr(arg[1]) <= 1 || \
my_getnbr(arg[1]) >= 100)
        return (84);
    map.map = prepare_map(my_getnbr(arg[1]));
    for (int i = 0; map.map[i] != NULL; i++)
        write(1, map.map[i], my_strlen(map.map[i]));
    write(1, "\n", 1);
    map.line = my_getnbr(arg[1]);
    map.match = my_getnbr(arg[2]);
    return (matchstick(map));
}
