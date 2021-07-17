/*
** EPITECH PROJECT, 2019
** end fight
** File description:
** end fight
*/

#include "my.h"

int game_over(rpg_t *r)
{
    for (int i = 0; i < 5; i++)
        if (r->player[i].stat.hp[0] > 0)
            return (0);
    return (1);
}

int fight_over(rpg_t *r)
{
    for (int i = 0; i < r->fight->nb_ennemies; i++)
        if (r->mob[i].stat.hp > 0)
            return (0);
    return (1);
}

void are_you_dead(rpg_t *r)
{
    int fd = 0;

    if (game_over(r)) {
        fd = open(".sav", O_TRUNC | O_WRONLY);
        close(fd);
        r->fight->choice = 0;
        r->fight->turn = -1;
        r->fight->way = 5;
        r->fight->go = 5;
        r->fight->resultat = 0;
        for (int i = 0; i < 10; i++)
            r->fight->stat[i].hp = 0;
        change_page(r, MENU);
    }
}

void is_end(rpg_t *r)
{
    if (fight_over(r)) {
        give_exp(r);
        r->fight->choice = 0;
        r->fight->turn = -1;
        r->fight->way = 5;
        r->fight->go = 5;
        r->fight->resultat = 0;
        for (int i = 0; i < 10; i++)
            r->fight->stat[i].hp = 0;
        change_page(r, MAP);
    }
}