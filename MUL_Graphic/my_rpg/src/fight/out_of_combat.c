/*
** EPITECH PROJECT, 2019
** out of combat
** File description:
** out of combat
*/

#include "my.h"

void run(rpg_t *r)
{
    r->fight->choice = 0;
    r->fight->turn = -1;
    r->fight->way = 5;
    r->fight->go = 5;
    r->fight->resultat = 0;
    for (int i = 0; i < 10; i++)
        r->fight->stat[i].hp = 0;
    change_page(r, MAP);
    return;
}

void give_exp(rpg_t *r)
{
    for (int i = 0; i < r->fight->nb_ennemies; i++) {
        r->inventory.gold += r->mob[i].stat.atk / 6 * pow(1.15,
        r->player[rand()% 5].level-1);
        for (int j = 0; j < 5; ++j) {
            if (r->player[j].stat.hp[0] > 0)
                r->player[j].stat.exp += r->mob[i].stat.atk / 6 * pow(1.15, r->\
player[rand() % 5].level-1);
            r->player[j].level = get_level(r->player[j].stat.exp);
        }
    }
}
