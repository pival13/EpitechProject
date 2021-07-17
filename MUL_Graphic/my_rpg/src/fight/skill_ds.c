/*
** EPITECH PROJECT, 2019
** skill_dm
** File description:
** skill of the mage demon
*/

#include "my.h"

void magic_arrow(rpg_t *w)
{
    int atk = calculate_atk(w, w->fight->turn) +
    w->fight->stat[w->fight->turn].atk;
    int res = w->mob[w->fight->go-5].stat.res+w->fight->stat[w->fight->go].res;
    int def = w->mob[w->fight->go-5].stat.def+w->fight->stat[w->fight->go].def;
    int stat = (def > res) ? res : def;

    if (anim(w, 0)) {
        if (atk - stat >= 1)
            w->mob[w->fight->go-5].stat.hp -= (atk - stat);
        else
            w->mob[w->fight->go-5].stat.hp -= 1;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[0];
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 4;
}

void resurrection(rpg_t *w)
{
    int nb = rand() % 5;

    for (int i = 0; i != 6; i++)
        if (i == 5) {
            w->player[w->fight->turn].stat.mp[0] -=
            w->player[w->fight->turn].cost[1];
            w->fight->turn = -1;
            w->fight->choice = 0;
            return;
        } else if (w->player[i].stat.hp[0] <= 0)
            break;
    if (anim(w, 0)) {
        for (; w->player[nb].stat.hp[0] > 0; nb = rand() % 5);
        w->player[nb].stat.hp[0] = w->player[nb].stat.hp[1] / 2;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[1];
        w->fight->turn = -1;
        w->fight->choice = 0, w->fight->skill = 0;
    } else
        w->fight->skill = 5;
}

void leech(rpg_t *w)
{
    if (anim(w, 0)) {
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[2];
        w->fight->stat[w->fight->turn].hp += 5;
        w->fight->stat[w->fight->go].hp -= 5;
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 6;
}

void invo_d(rpg_t *r)
{
    char **tab = (char *[3]){"magic arrow", "Resurrection", "Leech"};
    void (*funct[3])(rpg_t *) = {magic_arrow, resurrection, leech};

    print_button(r, tab);
    for (int i = 0; i != 3; i++)
        if ((r->fight->choice == 3+i && r->event.key.code == sfKeyReturn && \
r->event.type == sfEvtKeyReleased) || r->fight->skill == 4+i) {
            if (!check_mp(r, r->player[r->fight->turn].cost[i]))
                return;
            (*funct[i])(r);
        }
}
