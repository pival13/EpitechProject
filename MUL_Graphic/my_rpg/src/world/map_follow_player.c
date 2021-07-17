/*
** EPITECH PROJECT, 2019
** map_follow_player
** File description:
** move the map to follow the player
*/

#include "my.h"

void map_follow_player(rpg_t *w)
{
    sfVector2f pos = sfSprite_getPosition(w->map->diamond);

    if (pos.y < 0 || pos.y > SIZE(y) || pos.x < 0 || pos.x > SIZE(x))
        edit_map(w, (float[2]){0, 0}, (float[2]){0, 0}, 0);
    if (pos.y < SIZE(y)/4)
        edit_map(w, (float[2]){0, 0}, (float[2]){0, -0.15}, 0);
    if (pos.y > 3*SIZE(y)/4)
        edit_map(w, (float[2]){0, 0}, (float[2]){0, 0.15}, 0);
    if (pos.x < SIZE(x)/4)
        edit_map(w, (float[2]){0, 0}, (float[2]){-0.15, 0}, 0);
    if (pos.x > 3*SIZE(x)/4)
        edit_map(w, (float[2]){0, 0}, (float[2]){0.15, 0}, 0);
    edit_map(w, (float[2]){0, 0}, (float[2]){0, 0}, 0);
}
