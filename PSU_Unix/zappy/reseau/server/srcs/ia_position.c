/*
** EPITECH PROJECT, 2020
** Created by theo on 19/06/2020.
** File description:
** ia_command_inv.c
*/

#include "rfc_ia.h"

int closest_point(int current, int other, int map)
{
    int len = abs(current - other);
    if (len > abs(current - (other - map))) return (other - map);
    else if (len > abs(current - (other + map))) return (other + map);
    else return other;
}

int find_angle(player_t *current, player_t *other, map_t *map)
{
    int angle;
    float len;
    int x_other = closest_point(current->game->posX, other->game->posX, map->X);
    int y_other = closest_point(current->game->posY, other->game->posY, map->Y);

    int x_vector = current->game->posX - x_other;
    int y_vector = current->game->posY - y_other;
    if (x_vector == 0 && y_vector == 0) return 0;

    len = sqrt(pow(x_vector, 2) + pow(y_vector, 2));
    angle = (int)(acosf(y_vector / len) * 180 / 3.141591653);

    if (current->game->posX > x_other) angle = 360 - angle;
    angle += 360 - (current->game->orientation - 1) * 90;
    for (;angle >= 360; angle -= 360);

    return angle;
}