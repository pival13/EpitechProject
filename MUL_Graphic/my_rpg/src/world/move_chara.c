/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of my_world
*/

#include "my.h"

static int check_time(rpg_t *w)
{
    static sfTime time = {0};

    if (time.microseconds < sfClock_getElapsedTime(w->clock).microseconds - \
150000) {
        time = sfClock_getElapsedTime(w->clock);
        return (1);
    }
    return (0);
}

int is_good_cell(rpg_t *w, cell_t **map, int dx, int dy)
{
    cell_t cell;

    if (w->map->pos.y+dy < 0 || w->map->pos.x+dx < 0)
        return (-1);
    if (map[0][w->map->pos.x+1+dx].height == -100)
        return (-1);
    if (map[w->map->pos.y+1+dy] == NULL)
        return (-1);
    cell = map[w->map->pos.y+dy][w->map->pos.x+dx];
    if (cell.texture == 0)
        return (0);
    if (w->map->cur_map.y == 0 && cell.known == 0)
        return (0);
    return (1);
}

void heal_player(rpg_t *w)
{
    for (int i = 0; i != 5; i++) {
        w->player[i].stat.hp[0] += 2;
        w->player[i].stat.mp[0] += 2;
        if (w->player[i].stat.hp[0] > w->player[i].stat.hp[1])
            w->player[i].stat.hp[0] = w->player[i].stat.hp[1];
        if (w->player[i].stat.mp[0] > w->player[i].stat.mp[1])
            w->player[i].stat.mp[0] = w->player[i].stat.mp[1];
    }
}

void move_one_place_chara(rpg_t *w, int a)
{
    cell_t **map = w->map->map[w->map->cur_map.y][w->map->cur_map.x];

    if (is_good_cell(w, map, (a-2) % 2, (a-1) % 2) == 1) {
        (a % 2) ? (w->map->pos.x += a/2*2-1) : (w->map->pos.y += a/2*2-1);
    } else if (is_good_cell(w, w->map->map[w->map->cur_map.y + (a-1)%2][w->\
map->cur_map.x + (a-2) % 2], ((a-2)%2) * -24, ((a-1)%2) * -24) == 1) {
        if (a % 2 == 1) {
            w->map->cur_map.x += a / 2 * 2 - 1;
            w->map->pos.x = ((a+2)%4) / 2 * 24;
        } else {
            w->map->cur_map.y += a / 2 * 2 - 1;
            w->map->pos.y = ((a+2)%4) / 2 * 24;
        }
        edit_map(w, (float[2]){0, 0}, NULL, 0);
    }
    if (!(rand() % 15))
        change_page(w, FIGHT);
    heal_player(w);
}

void move_chara(rpg_t *w)
{
    cell_t **map = w->map->map[w->map->cur_map.y][w->map->cur_map.x];

    if (KEY(sfKeyUp) && is_good_cell(w, map, 0, -1) && check_time(w))
        move_one_place_chara(w, 0);
    if (KEY(sfKeyLeft) && is_good_cell(w, map, -1, 0) && check_time(w))
        move_one_place_chara(w, 1);
    if (KEY(sfKeyDown) && is_good_cell(w, map, 0, 1) && check_time(w))
        move_one_place_chara(w, 2);
    if (KEY(sfKeyRight) && is_good_cell(w, map, 1, 0) && check_time(w))
            move_one_place_chara(w, 3);
    if (w->map->cur_map.y != 0)
        w->map->map[0][0][(w->map->cur_map.y-1)*5+w->map->pos.y/5][w->map->cur\
_map.x*5+w->map->pos.x/5].known = 1;
    map_follow_player(w);
}
