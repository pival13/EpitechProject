/*
** EPITECH PROJECT, 2019
** edit_map
** File description:
** edit the map
*/

#include "my.h"

void calculate_map(rpg_t *w, int coeff, float angle[2], float init_pos[2])
{
    sfVector2f pos;
    sfVector2i i = w->map->pos;
    cell_t **map = w->map->map[w->map->cur_map.y][w->map->cur_map.x];

    for (int y = 0; map[y] != NULL; y++)
        for (int x = 0; map[y][x].height != -100; x++) {
            map[y][x].pos.x = (cos(angle[0])*y-sin(angle[0])*x - init_pos[0]) \
* coeff + SIZE(x)/2;
            map[y][x].pos.y = (-sin(angle[0])*sin(angle[1])*y-cos(angle[0])*si\
n(angle[1])*x - cos(angle[1])/2*map[y][x].height - init_pos[1]) * coeff + SIZE\
(y)/2;
        }
    pos.x = (map[i.y][i.x].pos.x + map[i.y+1][i.x].pos.x + map[i.y][i.x+1].pos\
.x + map[i.y+1][i.x+1].pos.x) / 4;
    pos.y = (map[i.y][i.x].pos.y + map[i.y+1][i.x].pos.y + map[i.y][i.x+1].pos\
.y + map[i.y+1][i.x+1].pos.y) / 4;
    sfSprite_setPosition(w->map->diamond, pos);
}

void edit_view(int *coeff, float *angle, float *change_angle)
{
    angle[0] += change_angle[0];
    angle[1] += change_angle[1];
    if (angle[1] < 0.1)
        angle[1] = 0.1;
    if (angle[1] > 1.57)
        angle[1] = 1.57;
    if (angle[0] < -3.14)
        angle[0] = -3.14;
    if (angle[0] > -1.57)
        angle[0] = -1.57;
    if (*coeff < 30)
        *coeff = 30;
    if (*coeff > 200)
        *coeff = 200;
}

void edit_pos(float *init_pos, float *change_pos)
{
    init_pos[0] += change_pos[0];
    init_pos[1] += change_pos[1];
}

void edit_map(rpg_t *w, float *ch_angle, float *ch_pos, float ch_size)
{
    static int coeff = 0;
    static float angle[2] = {-2.3561945, 0.5235988};
    static float init_pos[2] = {0, 0};

    if (ch_pos == NULL) {
        init_pos[0] = sqrt(2)/2*(w->map->pos.x - w->map->pos.y);
        init_pos[1] = -sin(angle[0])*sin(angle[1])*(w->map->pos.y) - cos(angle\
[0])*sin(angle[1])*(w->map->pos.x) + SIZE(y)/200;
    } else
        edit_pos(init_pos, ch_pos);
    if (ch_angle == NULL) {
        angle[0] = -2.3561945;
        angle[1] = 0.5235988;
        coeff = 100;
    } else {
        coeff += ch_size;
        edit_view(&coeff, angle, ch_angle);
    }
    calculate_map(w, coeff, angle, init_pos);
}
