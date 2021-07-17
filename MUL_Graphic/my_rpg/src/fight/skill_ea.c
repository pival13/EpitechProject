/*
** EPITECH PROJECT, 2019
** skill elf archer
** File description:
** skills of the elf's archer
*/

#include "my.h"

void sylvan_guard(rpg_t *w)
{
    int atk = calculate_atk(w, w->fight->turn) +
    w->fight->stat[w->fight->turn].atk;

    if (anim(w, 0)) {
        for (int i = 0; i != 5; i++)
            if (w->player[i].stat.hp[0] > 0) {
                w->player[i].stat.hp[0] += 0.2*atk;
                (w->player[i].stat.hp[0] > w->player[i].stat.hp[1]) ?
                (w->player[i].stat.hp[0] = w->player[i].stat.hp[1]) : (0);
            }
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[0];
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 10;
}

void piercing_shot(rpg_t *w)
{
    int atk = calculate_atk(w, w->fight->turn) +
    w->fight->stat[w->fight->turn].atk;
    int def = w->mob[w->fight->go-5].stat.def +
    w->fight->stat[w->fight->go].def;

    if (anim(w, 0)) {
        (atk - def >= 1) ?
        (w->mob[w->fight->go-5].stat.hp -= (atk - def))
        : (w->mob[w->fight->go-5].stat.hp -= 1);
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[1];
        w->fight->stat[w->fight->go].def -= 10;
        w->fight->stat[w->fight->go].res -= 10;
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 11;
}

void arrow_rain(rpg_t *w)
{
    int atk = calculate_atk(w, w->fight->turn) +
    w->fight->stat[w->fight->turn].atk;
    int def = 0;

    if (anim(w, 0)) {
        for (int i = 0; i != w->fight->nb_ennemies; i++) {
            def = w->mob[i].stat.def + w->fight->stat[5+i].def;
            (0.4 * atk - def >= 1) ?
            (w->mob[i].stat.hp -= (0.4 * atk - def))
            : (w->mob[i].stat.hp -= 1);
        }
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[2];
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 12;
}

void archery_e(rpg_t *r)
{
    char **tab = (char *[3]){"Sylvan Guard", "Piercing Shot", "Arrow's rain"};
    void (*funct[3])(rpg_t *) = {sylvan_guard, piercing_shot, arrow_rain};

    print_button(r, tab);
    for (int i = 0; i != 3; i++)
        if ((r->fight->choice == 3+i && r->event.key.code == sfKeyReturn && \
r->event.type == sfEvtKeyReleased) || r->fight->skill == 10+i) {
            if (!check_mp(r, r->player[r->fight->turn].cost[i]))
                return;
            (*funct[i])(r);
        }
}
