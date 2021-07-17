/*
** EPITECH PROJECT, 2019
** enemy stat
** File description:
** enemy stat
*/

#include "my.h"

void ennemi_stat(rpg_t *r)
{
    for (int i = 0; i < r->fight->nb_ennemies; i++) {
        r->mob[i].stat.hp = r->player[(rand() % 5)].stat.hp[1] + \
((rand() % 5) - 10);
        r->mob[i].stat.atk = calculate_atk(r, rand() % 5) + \
((rand() % 5) - 10);
        r->mob[i].stat.def = calculate_def(r, rand() % 5) + \
((rand() % 5) - 10);
        r->mob[i].stat.res = calculate_res(r, rand() % 5) + \
((rand() % 5) - 10);
        r->mob[i].stat.agi = 30 + rand() % 41;
    }
}