/*
** EPITECH PROJECT, 2019
** moved_ant
** File description:
** move an ant in in a new room
*/

#include "my.h"
#include "lemin.h"

void moved_ant(room_t *start_room, room_t *end_room)
{
    start_room->ant = 0;
    end_room->ant = 1;
    my_printf("P%s-%s", start_room->name, end_room->name);
}
