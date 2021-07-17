/*
** EPITECH PROJECT, 2019
** skill_og
** File description:
** skill of the ogre
*/

#include "my.h"

void fear(rpg_t *w)
{
    int atk = calculate_atk(w, w->fight->turn) +
    w->fight->stat[w->fight->turn].atk;
    int def = w->mob[w->fight->go-5].stat.def +
    w->fight->stat[w->fight->go].def;

    if (anim(w, 1)) {
        if (atk - def >= 1)
            w->mob[w->fight->go-5].stat.hp -= (atk - def);
        else
            w->mob[w->fight->go-5].stat.hp -= 1;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[0];
        w->fight->stat[w->fight->go].agi -= 10;
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 25;
}

void fury(rpg_t *w)
{
    int atk = calculate_atk(w, w->fight->turn) +
    w->fight->stat[w->fight->turn].atk;
    int def = w->mob[w->fight->go-5].stat.def +
    w->fight->stat[w->fight->go].def;

    if (anim(w, 1)) {
        if (atk - def >= 1)
            w->mob[w->fight->go-5].stat.hp -= (atk - def);
        else
            w->mob[w->fight->go-5].stat.hp -= 1;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[1];
        w->fight->stat[w->fight->turn].hp -= 5;
        w->fight->stat[w->fight->turn].atk += 20;
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 26;
}

void cannibalism2(rpg_t *w)
{
    w->fight->stat[w->fight->turn].atk += 10;
    w->fight->stat[w->fight->turn].def += 10;
    w->fight->stat[w->fight->turn].res += 10;
    w->fight->stat[w->fight->turn].agi += 10;
    w->fight->turn = -1;
    w->fight->choice = 0;
    w->fight->skill = 0;
}

void cannibalism(rpg_t *w)
{
    int nb = rand() % 4;
    int atk = calculate_atk(w, w->fight->turn) +
    w->fight->stat[w->fight->turn].atk;
    int def = calculate_def(w, nb) + w->fight->stat[nb].def;

    if (anim(w, 0)) {
        (atk * 0.7 - def >= 1) ? (w->player[nb].stat.hp[0] -= (atk * 0.7 - def))
        : (w->player[nb].stat.hp[0] -= 1);
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[2];
        w->player[w->fight->turn].stat.hp[0] += 20;
        if (w->player[w->fight->turn].stat.hp[0] >
            w->player[w->fight->turn].stat.hp[1])
            w->player[w->fight->turn].stat.hp[0] =
            w->player[w->fight->turn].stat.hp[1];
        cannibalism2(w);
    } else
        w->fight->skill = 27;
}

void ogre(rpg_t *r)
{
    char **tab = (char *[3]){"Fear", "fury", "cannibalism"};
    void (*funct[3])(rpg_t *) = {fear, fury, cannibalism};

    print_button(r, tab);
    for (int i = 0; i != 3; i++)
        if ((r->fight->choice == 3+i && r->event.key.code == sfKeyReturn && \
r->event.type == sfEvtKeyReleased) || r->fight->skill == 25+i) {
            if (!check_mp(r, r->player[r->fight->turn].cost[i]))
                return;
            (*funct[i])(r);
        }}
