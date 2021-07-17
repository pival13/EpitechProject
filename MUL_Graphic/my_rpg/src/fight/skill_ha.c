/*
** EPITECH PROJECT, 2019
** skill human archer
** File description:
** skill human archer
*/

#include "my.h"

void double_shot(rpg_t *w)
{
    int atk = w->player[w->fight->turn].stat.atk;
    int def = w->mob[w->fight->go-5].stat.def +
    w->fight->stat[w->fight->go].def;

    if (anim(w, 0)) {
        (atk - def >= 1) ? (w->mob[w->fight->go-5].stat.hp -= (atk - def))
        : (w->mob[w->fight->go-5].stat.hp -= 1);
        if (w->fight->go-4 <= w->fight->nb_ennemies) {
            def = w->mob[w->fight->go-4].stat.def +
            w->fight->stat[w->fight->go+1].def;
            (atk - def >= 1) ? (w->mob[w->fight->go-4].stat.hp -= (atk - def))
            : (w->mob[w->fight->go-4].stat.hp -= 1);
        }
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[0];
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 16;
}

void weak_point(rpg_t *w)
{
    int atk = w->player[w->fight->turn].stat.atk;
    int def = w->mob[w->fight->go-5].stat.def +
    w->fight->stat[w->fight->go].def;

    if (anim(w, 0)) {
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
        w->fight->skill = 17;
}

void explosiv_arrow(rpg_t *w)
{
    int atk = w->player[w->fight->turn].stat.atk;
    int def = w->mob[w->fight->go-5].stat.def +
    w->fight->stat[w->fight->go].def;

    if (anim(w, 0)) {
        if (atk * 1.1 - def >= 1)
            w->mob[w->fight->go-5].stat.hp -= (atk * 1.1 - def);
        else
            w->mob[w->fight->go-5].stat.hp -= 1;
        w->player[w->fight->turn].stat.mp[0] -=
        w->player[w->fight->turn].cost[2];
        w->fight->stat[w->fight->go].hp -= 5;
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = 18;
}

void archery_h(rpg_t *r)
{
    char **tab = (char *[3]){"Double Shot", "Weak Point", "Explosive Arrow"};
    void (*funct[3])(rpg_t *) = {double_shot, weak_point, explosiv_arrow};

    print_button(r, tab);
    for (int i = 0; i != 3; i++)
        if ((r->fight->choice == 3+i && r->event.key.code == sfKeyReturn && \
r->event.type == sfEvtKeyReleased) || r->fight->skill == 16+i) {
            if (!check_mp(r, r->player[r->fight->turn].cost[i]))
                return;
            (*funct[i])(r);
        }
}
