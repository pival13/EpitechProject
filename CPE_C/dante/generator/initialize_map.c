/*
** EPITECH PROJECT, 2019
** hunt_kill
** File description:
** hunt and kill algo
*/

#include "dante.h"

void load_line(char **map, int nb, int len)
{
    for (int i = 0; i != len; i++) {
        if (nb % 2 == 0) {
            if (i % 2 == 0)
                map[nb][i] = '.';
            else
                map[nb][i] = ' ';
        } else {
            if (i % 2 == 0)
                map[nb][i] = ' ';
            else
                map[nb][i] = 'X';
        }
    }
    map[nb][len] = '\0';
}

char **initialize_map(int x, int y)
{
    char **map = malloc(sizeof(char *) * (y+1));
    if (map == NULL) return (NULL);
    for (int i = 0; i != y; i++) {
        map[i] = malloc(sizeof(char) * x+1);
        if (map[i] == NULL) return (NULL);
        load_line(map, i, x);
    }
    map[y] = NULL;
    return (map);
}