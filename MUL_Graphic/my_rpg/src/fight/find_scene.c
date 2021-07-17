/*
** EPITECH PROJECT, 2019
** find scene
** File description:
** background
*/

#include "my.h"

int find_scene(rpg_t *r)
{
    int tab[6] = {DEMON, PLAIN, FOREST, MOUNTAIN, CITY, SWAMP};
    int i = r->map->map[r->map->cur_map.y][r->map->cur_map.x][r->map->pos.y]\
[r->map->pos.x].texture;

    return (tab[i-1]);
}