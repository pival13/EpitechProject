/*
** EPITECH PROJECT, 2019
**  main
** File description:
** main of lemin
*/

#include "my.h"
#include "lemin.h"
#include <stdlib.h>

room_t *find_room(room_t *room, char *name, int nb)
{
    room_t *alt;

    if (my_strcmp(room->name, name) == 0)
        return (room);
    else if (nb > 10) return (NULL);
    for (int i = 0; room->link[i] != NULL; i++) {
        alt = find_room(room->link[i], name, nb+1);
        if (alt != NULL)
            return (alt);
    }
    return (NULL);
}
