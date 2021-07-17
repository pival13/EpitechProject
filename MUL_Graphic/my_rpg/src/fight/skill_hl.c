/*
** EPITECH PROJECT, 2019
** skill human lance
** File description:
** skill of human lancer
*/

#include "my.h"

void barrage(rpg_t *w)
{
    int atk = w->player[w->fight->turn].stat.atk;
    int def = w->mob[w->fight->go-5].stat.def+w->fight->stat[w->fight->go].def;
    int nb = rand() % 5 + 1;

    if (anim(w, 1)) {
        if (nb*0.3*atk - def >= 1)
            w->mob[w->fight->go-5].stat.hp -= (nb*0.3*atk - def);
        else
            w->mob[w->fight->go-5].stat.hp -= 1;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[0];
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 19;
}

void piercing(rpg_t *w)
{
    int atk = w->player[w->fight->turn].stat.atk;
    int def = w->mob[w->fight->go-5].stat.def+w->fight->stat[w->fight->go].def;

    if (anim(w, 1)) {
        if (atk * 1.1 - def >= 1)
            w->mob[w->fight->go-5].stat.hp -= (atk * 1.1 - def);
        else
            w->mob[w->fight->go-5].stat.hp -= 1;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[1];
        w->fight->stat[w->fight->go].def -= 5;
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 20;
}

void slash(rpg_t *w)
{
    int atk = w->player[w->fight->turn].stat.atk;
    int def = w->mob[w->fight->go-5].stat.def+w->fight->stat[w->fight->go].def;

    if (anim(w, 1) != 0) {
        w->fight->skill = 0;
        if (1.2 * atk - def >= 1)
            w->mob[w->fight->go-5].stat.hp -= (1.2 * atk - def);
        else
            w->mob[w->fight->go-5].stat.hp -= 1;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[2];
        w->fight->turn = -1;
        w->fight->choice = 0;
    }
    else
        w->fight->skill = 21;
}

void lancer_h(rpg_t *r)
{
    char **tab = (char *[3]){"barrage", "piercing", "slash"};
    void (*funct[3])(rpg_t *) = {barrage, piercing, slash};

    print_button(r, tab);
    for (int i = 0; i != 3; i++)
        if ((r->fight->choice == 3+i && r->event.key.code == sfKeyReturn && \
r->event.type == sfEvtKeyReleased) || r->fight->skill == 19+i) {
            if (!check_mp(r, r->player[r->fight->turn].cost[i]))
                return;
            (*funct[i])(r);
        }
}
