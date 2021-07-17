/*
** EPITECH PROJECT, 2019
** check_time_attack
** File description:
** check when a player have to fight
*/

#include "my.h"

void life_per_turn(rpg_t *w, sfTime *time)
{
    for (int i = 0; i != 5+w->fight->nb_ennemies; i++)
        if (i < 5 && w->player[i].stat.hp[0] > 0) {
            w->player[i].stat.hp[0] += w->fight->stat[i].hp;
            if (w->player[i].stat.hp[0] > w->player[i].stat.hp[1])
                w->player[i].stat.hp[0] = w->player[i].stat.hp[1];
        } else if (i > 5)
            w->mob[i-5].stat.hp += w->fight->stat[i].hp;
    time[10] = sfClock_getElapsedTime(w->clock);
}

void get_time_chara(rpg_t *w, int i, sfTime *time, sfTime *save)
{
    int agi = 0;

    if (i < 5)
        agi = calculate_agi(w, i) + w->fight->stat[i].agi;
    else
        agi = w->mob[i-5].stat.agi + w->fight->stat[i].agi;
    if (sfClock_getElapsedTime(w->clock).microseconds > time[i].microseconds \
+ 2000000 - agi * 10000) {
        time[i] = sfClock_getElapsedTime(w->clock);
        w->fight->stat[i].agi = 0;
        if ((i < 5 && w->player[i].stat.hp[0] > 0) || (i > 4 && w->mob[i-5].\
stat.hp > 0))
            w->fight->turn = i;
        for (int i = 0; i != 5 + w->fight->nb_ennemies; i++)
            save[i].microseconds = sfClock_getElapsedTime(w->clock).\
microseconds - time[i].microseconds;
        save[10].microseconds = sfClock_getElapsedTime(w->clock).\
microseconds - time[10].microseconds;
    }
}

void check_time_fight(rpg_t *w)
{
    static sfTime tim[11] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, {0}};
    static sfTime sav[11] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
    {0}, {0}, {0}};

    if (w->fight->resultat == 0) {
        for (int i = 0; i != 11; tim[i++] = sfClock_getElapsedTime(w->clock));
        return;
    }
    for (int i = 0; i != 5+w->fight->nb_ennemies && w->fight->turn == -1; i++)
        get_time_chara(w, i, tim, sav);
    for (int i = 0; i != 5+w->fight->nb_ennemies && w->fight->turn != -1; i++)
        tim[i].microseconds = sfClock_getElapsedTime(w->clock).microseconds - \
sav[i].microseconds;
    if (w->fight->turn != -1)
        tim[10].microseconds = sfClock_getElapsedTime(w->clock).microseconds - \
sav[10].microseconds;
    if (tim[10].microseconds + 500000 <
    sfClock_getElapsedTime(w->clock).microseconds)
        life_per_turn(w, tim);
}
