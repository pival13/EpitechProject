/*
** EPITECH PROJECT, 2019
** skill human thief
** File description:
** skill of the human thief
*/

#include "my.h"

void sneak(rpg_t *w)
{
    int atk = w->player[w->fight->turn].stat.atk;
    int def = w->mob[w->fight->go-5].stat.def +
    w->fight->stat[w->fight->go].def;

    if (anim(w, 1)) {
        if (atk - def * 0.7 >= 1)
            w->mob[w->fight->go-5].stat.hp -= (atk - def * 0.7);
        else
            w->mob[w->fight->go-5].stat.hp -= 1;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[0];
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 22;
}

void taste_of_blood(rpg_t *w)
{
    int atk = w->player[w->fight->turn].stat.atk;
    int def = w->mob[w->fight->go-5].stat.def +
    w->fight->stat[w->fight->go].def;

    if (anim(w, 1)) {
        if (0.8 * atk - def >= 1)
            w->mob[w->fight->go-5].stat.hp -= (0.8 * atk - def);
        else
            w->mob[w->fight->go-5].stat.hp -= 1;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[1];
        w->fight->stat[w->fight->go].hp -= 5;
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 23;
}

void blood_lust(rpg_t *w)
{
    int atk = w->player[w->fight->turn].stat.atk;
    int def = w->mob[w->fight->go-5].stat.def +
    w->fight->stat[w->fight->go].def;

    if (anim(w, 1)) {
        if (atk * 0.7 - def >= 1)
            w->mob[w->fight->go-5].stat.hp -= (atk * 0.7 - def);
        else
            w->mob[w->fight->go-5].stat.hp -= 1;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[2];
        w->fight->stat[w->fight->turn].agi += 50;
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 24;
}

void thief_h(rpg_t *r)
{
    char **tab = (char *[3]){"Sneak", "Taste of blood", "Blood-lust"};
    void (*funct[3])(rpg_t *) = {sneak, taste_of_blood, blood_lust};

    print_button(r, tab);
    for (int i = 0; i != 3; i++)
        if ((r->fight->choice == 3+i && r->event.key.code == sfKeyReturn && \
r->event.type == sfEvtKeyReleased) || r->fight->skill == 22+i) {
            if (!check_mp(r, r->player[r->fight->turn].cost[i]))
                return;
            (*funct[i])(r);
        }
}
