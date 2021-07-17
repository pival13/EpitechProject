/*
** EPITECH PROJECT, 2019
** create_map
** File description:
** create the map of world
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "my.h"
#include "my_world.h"

int nb_columns(char *map)
{
    int i = 0;
    for (int k = 0; map[k] != '\0'; ++k)
        if (map[k] == '|')i++;
    i++;
    return i;
}

int nb_lines(char **map)
{
    int i = 0;
    for (; map[i] != NULL; ++i);
    i++;
    return i;
}

cell_t **fill_map(int y, int x, world_t *w, char **world)
{
    int k = 0;
    int i = 0;

    w->map[y - 1][x - 1].shape = sfConvexShape_create();
    sfConvexShape_setPointCount(w->map[y - 1][x - 1].shape, 4);
    sfConvexShape_setOutlineColor(w->map[y - 1][x - 1].shape, sfBlack);
    sfConvexShape_setOutlineThickness(w->map[y - 1][x - 1].shape, 1);
    for (i = 1; i != x; i++) {
        for (; world[y-1][k] == '-' || (world[y-1][k] >= '0' && world[y-1]\
[k] <= '9'); k++);
        k++;
        for (; world[y-1][k] >= '0' && world[y-1][k] <= '9'; k++);
        k++;
    }
    for (; world[y-1][k] == '-' || (world[y-1][k] >= '0' && world[y-1]\
[k] <= '9'); k++);
    k++;
    sfConvexShape_setTexture(w->map[y - 1][x - 1].shape, w->texture[my_getnbr\
(&world[y-1][k])], sfTrue);
    return (w->map);
}

void load_map(world_t *w, char **map)
{
    int j = 0;
    int k = 0;
    int i = 0;
    w->map = malloc(sizeof(cell_t *) *(nb_lines(map) + 1));
    for (; map[i] != NULL; i++) {
        w->map[i] = malloc(sizeof(cell_t) *(nb_columns(map[i]) + 1));
        for (j = 0, k = 0; map[i][k] != '\n' && map[i][k] != '\0'; j++, k++) {
            w->map[i][j].height = my_getnbr(&map[i][k]);
            for (; map[i][k] == '-' || (map[i][k] <= '9' && map[i]\
[k] >= '0'); k++);
            k++;
            if (i > 0 && j > 0) w->map = fill_map(i, j, w, map);
            for (; map[i][k] >= '0' && map[i][k] <= '9'; k++);
        }
        w->map[i][j].height = -100;
        if (i > 0) free(map[i-1]);
    }
    free(map[i-1]);
    w->map[i] = NULL;
    free(map);
}
