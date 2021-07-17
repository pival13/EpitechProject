/*
** EPITECH PROJECT, 2019
** main solver
** File description:
** main of solver
*/

#include "dante.h"

int main(int n, char **arg)
{
    solver_t map;

    if (n != 2)
        return (84);
    create_map(arg[1], &map);
    map.len = my_strlen(map.map) + 1;
    solver(&map);
    if (map.map[strlen(map.map)-1] == 'o')
        my_printf("%s", map.map);
    return (0);
}
