/*
** EPITECH PROJECT, 2019
** get_level
** File description:
** get the current level
*/

#include "my.h"

int get_level(int exp)
{
    int level = 1;

    for (int i = 1; 1; i++) {
        exp -= (int)(100 * pow(1.1, i-1));
        if (exp >= 0)
            level++;
        else
            break;
    }
    return (level);
}

void complete_players(rpg_t *w)
{
    int race[10] = {DEMONF, DEMONH, NAINF, NAINH, ELFF, ELFH, HUMANF, HUMANH, \
OGREF, OGREH};
    int nb[30] = {6, 8, 0, 5, 8, 0, 7, 0, 0, 6, 0, 0, 5, 6, 0, 5, 7, 0, 5, 5, \
7, 5, 6, 6, 5, 0, 0, 5, 0, 0};
    int cost[45] = {20, 30, 30, 15, 20, 30, 0, 0, 0, 25, 10, 20, 0, 0, 0, 0, 0\
, 0, 5, 15, 25, 25, 25, 25, 0, 0, 0, 10, 15, 20, 5, 15, 15, 20, 10, 20, 10, 30\
, 5, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i != 5; i++) {
        w->player[i].level = get_level(w->player[i].stat.exp);
        w->player[i].stat.hp[0] = w->player[i].stat.hp[1];
        w->player[i].stat.mp[0] = w->player[i].stat.mp[1];
        w->player[i].texture = w->textures[race[2*i+w->player[i].sexe] + 1 + \
w->player[i].classe];
        w->player[i].nb_sprite = nb[i*6 + w->player[i].sexe*3 + w->player[i].\
classe];
        w->player[i].cost[0] = cost[i*9+w->player[i].classe*3];
        w->player[i].cost[1] = cost[i*9+w->player[i].classe*3+1];
        w->player[i].cost[2] = cost[i*9+w->player[i].classe*3+2];
    }
}
