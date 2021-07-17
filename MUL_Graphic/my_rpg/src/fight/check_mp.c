/*
** EPITECH PROJECT, 2019
** check mp
** File description:
** check p
*/

#include "my.h"

int check_mp(rpg_t *r, int cost)
{
    if (cost > r->player[r->fight->turn].stat.mp[0]) {
        r->fight->nomana = 1;
        return (0);
    }
    return (1);
}