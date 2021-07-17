/*
** EPITECH PROJECT, 2019
** skill_dm
** File description:
** skill of the mage demon
*/

#include "my.h"

void fireball(rpg_t *w)
{
    int atk = calculate_atk(w, w->fight->turn) +
    w->fight->stat[w->fight->turn].atk;
    int res = w->mob[w->fight->go-5].stat.res+w->fight->stat[w->fight->go].res;

    if (anim(w, 0)) {
        if (atk * 0.8 - res >= 1)
            w->mob[w->fight->go-5].stat.hp -= (atk * 0.8 - res);
        else
            w->mob[w->fight->go-5].stat.hp -= 1;
        w->fight->stat[w->fight->go].hp -= 5;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[0];
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 1;
}

void electric_shot(rpg_t *w)
{
    int atk = calculate_atk(w, w->fight->turn) +
    w->fight->stat[w->fight->turn].atk;
    int res = w->mob[w->fight->go-5].stat.res+w->fight->stat[w->fight->go].res;

    if (anim(w, 0)) {
        if (atk * 1.3 - res >= 1)
            w->mob[w->fight->go-5].stat.hp -= (atk * 1.3 - res);
        else
            w->mob[w->fight->go-5].stat.hp -= 1;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[1];
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 2;
}

void life_drain(rpg_t *w)
{
    int atk = calculate_atk(w, w->fight->turn) +
    w->fight->stat[w->fight->turn].atk;
    int res = w->mob[w->fight->go-5].stat.res+w->fight->stat[w->fight->go].res;

    if (anim(w, 0)) {
        (atk - res >= 1) ? (w->mob[w->fight->go-5].stat.hp -= (atk - res)) :
        (w->mob[w->fight->go-5].stat.hp -= 1);
        w->player[w->fight->turn].stat.hp[0] += (atk - res) / 3;
        if (w->player[w->fight->turn].stat.hp[0] >
            w->player[w->fight->turn].stat.hp[1])
            w->player[w->fight->turn].stat.hp[0] =
            w->player[w->fight->turn].stat.hp[1];
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[2];
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 3;
}

void mage_d(rpg_t *r)
{
    char **tab = (char *[3]){"Fireball", "Electric Shot", "Life Drain"};
    void (*funct[3])(rpg_t *) = {fireball, electric_shot, life_drain};

    print_button(r, tab);
    for (int i = 0; i != 3; i++)
        if ((r->fight->choice == 3+i && r->event.key.code == sfKeyReturn && \
r->event.type == sfEvtKeyReleased) || r->fight->skill == 1+i) {
            if (!check_mp(r, r->player[r->fight->turn].cost[i]))
                return;
            (*funct[i])(r);
        }
}
