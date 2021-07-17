/*
** EPITECH PROJECT, 2019
** ground.c
** File description:
** draw and move the ground
*/

#include "csfml.h"
#include <stdlib.h>

void draw_ground(sfRenderWindow *window, object_t **obj, map_t **map)
{
    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j].type != '\0'; j++) {
            if (map[i][j].type == '#' && map[i-1][j].type != '#') {
                sfSprite_setPosition(obj[GRASS]->sprite, map[i][j].move);
                sfRenderWindow_drawSprite(window, obj[GRASS]->sprite, NULL);
            } else if (map[i][j].type == '#') {
                sfSprite_setPosition(obj[GROUND]->sprite, map[i][j].move);
                sfRenderWindow_drawSprite(window, obj[GROUND]->sprite, NULL);
            }
            if (map[i][j].type == 'M') {
                sfSprite_setPosition(obj[SPIKE]->sprite, map[i][j].move);
                sfRenderWindow_drawSprite(window, obj[SPIKE]->sprite, NULL);
            }
        }
}

void move_ground(sfRenderWindow *window, object_t **obj, map_t **map, \
sfClock *clock)
{
    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j].type != '\0'; j++) {
            map[i][j].move.x = -100 * sfClock_getElapsedTime(clock).\
microseconds / 1000000 + map[i][j].pos.x;
            map[i][j].move.y = map[i][j].pos.y;
        }
    draw_ground(window, obj, map);
    if (map[9][1].move.x < 0)
        for (int i = 0; map[i] != NULL; i++)
            for (int j = 0; map[i][j].type != '\0'; j++) {
                map[i][j] = map[i][j+1];
            }
}
