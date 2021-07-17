/*
** EPITECH PROJECT, 2019
** create map
** File description:
** create the map
*/

#include "my.h"

int nb_columns(char *map)
{
    int i = 0;

    for (int k = 0; map[k] != '\0'; ++k)
        if (map[k] == '|')
            i++;
    i++;
    return i;
}

void fill_map(int y, int x, cell_t **map, char **world)
{
    int k = 0;
    int i = 0;

    for (i = 1; i != x; i++) {
        for (; world[y-1][k] == '-' || (world[y-1][k] >= '0' && world[y-1]\
[k] <= '9'); k++);
        k++;
        for (; world[y-1][k] >= '0' && world[y-1][k] <= '9'; k++);
        k++;
    }
    for (; world[y-1][k] == '-' || (world[y-1][k] >= '0' && world[y-1]\
[k] <= '9'); k++);
    map[y-1][x-1].texture = my_getnbr(&world[y-1][k+1]);
    if (map[y-1][x-1].texture == 0)
        map[y-1][x-1].known = 1;
    else
        map[y-1][x-1].known = 0;
}

cell_t **load_map(char **m)
{
    int j = 0;
    int k = 0;
    int i = 0;
    cell_t **map = malloc(sizeof(cell_t *) * (nb_row(m) + 1));

    for (; m != NULL && m[i] != NULL; i++) {
        map[i] = malloc(sizeof(cell_t) * (nb_columns(m[i]) + 1));
        for (j = 0, k = 0; m[i][k] != '\0'; j++, k++) {
            map[i][j].height = my_getnbr(&m[i][k]);
            for (; m[i][k] == '-' || (m[i][k] <= '9' && m[i][k] >= '0'); k++);
            (i > 0 && j > 0) ? (fill_map(i, j, map, m)) : (0);
            for (k += 1; m[i][k] >= '0' && m[i][k] <= '9'; k++);
        }
        map[i][j].height = -100;
    }
    map[i] = NULL;
    return (map);
}
