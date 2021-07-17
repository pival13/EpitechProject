/*
** EPITECH PROJECT, 2019
** enemy_turn
** File description:
** make attack the enemy
*/

#include "my.h"

void enemy_turn(rpg_t *w, sfVector2f pos)
{
    static sfTime ti = {0};
    int tar = rand() % 5;
    int stat[2] = {0, w->mob[w->fight->turn-5].stat.atk +
w->fight->stat[w->fight->turn].atk};

    sfMusic_play(w->sounds[S_FIGHT]);
    (ti.microseconds == 0) ? (ti = sfClock_getElapsedTime(w->clock)) : (ti);
    if (ti.MS + 1000000 > sfClock_getElapsedTime(w->clock).microseconds) {
        text_draw(w, "enemy turn", pos, sfWhite);
        return;
    }
    for (; w->player[tar].stat.hp[0] <= 0; tar = rand() % 5);
    (w->fight->which[w->fight->turn-5] == SHAGGY) ?
    (stat[0] = calculate_res(w, tar) + w->fight->stat[tar].res) :
    (stat[0] = calculate_def(w, tar) + w->fight->stat[tar].def);
    (stat[1] - stat[0] > 1) ? (w->player[tar].stat.hp[0] -= stat[1] - stat[0]) :
    (w->player[tar].stat.hp[0] -= 1);
    (w->player[tar].stat.hp[0] < 0) ? (w->player[tar].stat.hp[0] = 0) : (0);
    ti.microseconds = 0;
    w->fight->turn = -1;
}
