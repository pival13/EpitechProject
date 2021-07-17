/*
** EPITECH PROJECT, 2019
** skill elf mage
** File description:
** skills of the elf's mage
*/

#include "my.h"

void root_trap(rpg_t *w)
{
    int atk = calculate_atk(w, w->fight->turn) +
    w->fight->stat[w->fight->turn].atk;
    int res = w->mob[w->fight->go-5].stat.res +
    w->fight->stat[w->fight->go].res;

    if (anim(w, 0)) {
        if (atk * 0.7 - res >= 1)
            w->mob[w->fight->go-5].stat.hp -= (atk * 0.7 - res);
        else
            w->mob[w->fight->go-5].stat.hp -= 1;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[0];
        w->fight->stat[w->fight->go].agi -= 200;
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 13;
}

void blossom(rpg_t *w)
{
    int atk = calculate_atk(w, w->fight->turn) +
    w->fight->stat[w->fight->turn].atk;
    int res = w->mob[w->fight->go-5].stat.res+w->fight->stat[w->fight->go].res;

    if (anim(w, 0)) {
        (atk * 0.8 - res >= 1) ? (w->mob[w->fight->go-5].stat.hp
        -= (atk * 0.8 - res)) : (w->mob[w->fight->go-5].stat.hp -= 1);
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[1];
        for (int i = 0; i != 5; i++)
            if (w->player[i].stat.hp[0] > 0 && i != w->fight->turn) {
                w->fight->stat[i].atk += 5;
                w->fight->stat[i].def += 5;
                w->fight->stat[i].res += 5;
            }
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 14;
}

void holy_blessing(rpg_t *w)
{
    if (anim(w, 0)) {
        for (int i = 0; i != 5; i++)
            w->fight->stat[i].hp += 5;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[2];
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 15;
}

void mage_e(rpg_t *r)
{
    char **tab = (char *[3]){"Root's trap", "Blossom", "holy blessing"};
    void (*funct[3])(rpg_t *) = {root_trap, blossom, holy_blessing};

    print_button(r, tab);
    for (int i = 0; i != 3; i++)
        if ((r->fight->choice == 3+i && r->event.key.code == sfKeyReturn && \
r->event.type == sfEvtKeyReleased) || r->fight->skill == 13+i) {
            if (!check_mp(r, r->player[r->fight->turn].cost[i]))
                return;
            (*funct[i])(r);
        }
}
