/*
** EPITECH PROJECT, 2019
** calculate stat
** File description:
** calculate the stat
*/

#include "my.h"

int calculate_atk(rpg_t *w, int nb)
{
    int atk = w->player[nb].stat.atk + w->player[nb].level - 1;

    for (int i = 0; i != 5; i++)
        if (w->player[nb].equip[i].name != NULL)
            atk += w->player[nb].equip[i].stat.atk;
    return (atk);
}

int calculate_def(rpg_t *w, int nb)
{
    int def = w->player[nb].stat.def + w->player[nb].level - 1;

    for (int i = 0; i != 5; i++)
        if (w->player[nb].equip[i].name != NULL)
            def += w->player[nb].equip[i].stat.def;
    return (def);
}

int calculate_res(rpg_t *w, int nb)
{
    int res = w->player[nb].stat.res + w->player[nb].level - 1;

    for (int i = 0; i != 5; i++)
        if (w->player[nb].equip[i].name != NULL)
            res += w->player[nb].equip[i].stat.res;
    return (res);
}

int calculate_agi(rpg_t *w, int nb)
{
    int agi = w->player[nb].stat.agi + w->player[nb].level - 1;

    for (int i = 0; i != 5; i++)
        if (w->player[nb].equip[i].name != NULL)
            agi += w->player[nb].equip[i].stat.agi;
    return (agi);
}