/*
** EPITECH PROJECT, 2019
** main bonus
** File description:
** main bonus of solver
*/

#include "dante.h"

void print_map(char *map)
{
    for (int i = 0; map[i] != '\0'; i++) {
        if (map[i] == 'o') {
            printf("\e[7;33m%c\e[0m", map[i]);
        } else if (map[i] == 'X') {
            printf("\e[7;34m%c\e[0m", map[i]);
        } else {
            printf("\e[7m%c\e[0m", map[i]);
        }
    }
    printf("\n");
}

int main(int n, char **arg)
{
    solver_t map;

    if (n != 3) {
        my_printf("Please enter a map and a number between 0 and 3\n");
        return (84);
    }
    create_map(arg[1], &map);
    map.len = my_strlen(map.map) + 1;
    if (!is_good_map(map.map)) {
        my_printf("Invalid map\n");
        exit(84);
    }
    if (map.map[(int)strlen(map.map)-1] != '*' || map.map[0] != '*')
        return (printf("no solution found\n"));
    solver_b(&map, atoi(arg[2]));
    if (map.map[strlen(map.map)-1] == 'o')
        print_map(map.map);
}