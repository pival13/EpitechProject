/*
** EPITECH PROJECT, 2019
** skill human thief
** File description:
** skill of the human thief
*/

#include "my.h"

void shield_bash(rpg_t *w)
{
    int atk = w->player[w->fight->turn].stat.atk;
    int def = w->mob[w->fight->go-5].stat.def +
    w->fight->stat[w->fight->go].def;

    if (anim(w, 1) != 0) {
        (atk * 0.7 - def >= 1) ?
        (w->mob[w->fight->go-5].stat.hp -= (atk * 0.7 - def))
        : (w->mob[w->fight->go-5].stat.hp -= 1);
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[0];
        w->fight->stat[w->fight->go].agi -= 200;
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 7;
}

void taunt(rpg_t *w)
{
    int atk = w->player[w->fight->turn].stat.atk;
    int def = w->mob[w->fight->go-5].stat.def +
    w->fight->stat[w->fight->go].def;

    if (anim(w, 1) != 0) {
        (atk - def >= 1) ?
        (w->mob[w->fight->go-5].stat.hp -= (atk - def))
        : (w->mob[w->fight->go-5].stat.hp -= 1);
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[1];
        w->fight->stat[w->fight->turn].def += 15;
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 8;
}

void slaughter(rpg_t *w)
{
    int atk = w->player[w->fight->turn].stat.atk;
    int def = w->mob[w->fight->go-5].stat.def +
    w->fight->stat[w->fight->go].def;

    if (anim(w, 1) != 0) {
        (atk * 1.5 - def >= 1) ?
        (w->mob[w->fight->go-5].stat.hp -= (atk * 1.5 - def))
        : (w->mob[w->fight->go-5].stat.hp -= 1);
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[2];
        w->fight->stat[w->fight->turn].agi += 50;
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 9;
}

void dwarf(rpg_t *r)
{
    char **tab = (char *[3]){"Shield bash", "Taunt", "Slaughter"};
    void (*funct[3])(rpg_t *) = {shield_bash, taunt, slaughter};

    print_button(r, tab);
    for (int i = 0; i != 3; i++)
        if ((r->fight->choice == 3+i && r->event.key.code == sfKeyReturn && \
r->event.type == sfEvtKeyReleased) || r->fight->skill == 7+i) {
            if (!check_mp(r, r->player[r->fight->turn].cost[i]))
                return;
            (*funct[i])(r);
        }
}
