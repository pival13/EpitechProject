/*
** EPITECH PROJECT, 2019
** rooms_len.c
** File description:
** rooms len
*/

#include "my.h"

int rooms_len(lemin_t *w)
{
    room_t **room_count = w->tab_room;
    int i = 0;

    for (i = 0; room_count[i] != NULL; i++);
    return (i);
}

int way_finished(int *way)
{
    int i = 0;

    for (i = 0; way[i] != -1; i++);
    i--;
    if (i < 0 || way[i] == -2)
        return (1);
    return (0);
}

int in_mem(room_t *room, char **mem)
{
    for (int i = 0; mem[i] != NULL; i++) {
        if (my_strcmp(room->name, mem[i]) == 0)
            return (1);
    }
    return (0);
}
