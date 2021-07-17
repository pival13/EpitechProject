/*
** EPITECH PROJECT, 2019
**  low attack
** File description:
** low attack
*/

#include "my.h"

void in_attack(rpg_t *r, int which)
{
    sfColor color = (sfColor){150, 150, 150, 255};

    for (int i = 0; i < 5+r->fight->nb_ennemies; i++) {
        if (i == which)
            sfSprite_setColor(r->fight->sprite[which], sfWhite);
        else
            sfSprite_setColor(r->fight->sprite[i], color);
    }
}

void little_attack(rpg_t *w)
{
    int target = w->fight->go;
    int def = 0;
    int atk = calculate_atk(w, w->fight->turn) + w->fight->stat[w->fight->turn]\
.atk;
    int animation[15] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0};

    if (!KEY_R(sfKeyReturn) && w->fight->skill != -1)
        return;
    if (anim(w, animation[3 * w->fight->turn + w->player[w->fight->turn].classe\
]) != 0) {
        def = w->mob[target-5].stat.def + w->fight->stat[target].def;
        if (atk - def > 1)
            w->mob[target-5].stat.hp -= atk - def;
        else
            w->mob[target-5].stat.hp -= 1;
        w->fight->turn = -1;
        w->fight->choice = 0;
        w->fight->skill = 0;
    } else
        w->fight->skill = -1;
}
