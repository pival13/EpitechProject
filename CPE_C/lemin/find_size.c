/*
** EPITECH PROJECT, 2019
** find size
** File description:
** find size
*/

#include "my.h"
#include "lemin.h"

int nb_link(room_t *room)
{
    int i = 0;

    for (; room->link[i] != NULL; i++);
    return (i);
}

int nb_room(lemin_t *w)
{
    int i = 0;

    for (; w->tab_room[i] != NULL; i++);
    return (i);
}

