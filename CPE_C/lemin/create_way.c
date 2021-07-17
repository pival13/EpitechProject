/*
** EPITECH PROJECT, 2019
** create way
** File description:
** create all the way for the ant
*/

#include "my.h"

int already_exist(room_t ***way, room_t *room, lemin_t *w)
{
    for (int i = 0; way[i] != NULL; i++)
        for (int j = 0; way[i][j] != NULL; j++)
            if (way[i][j] == room && room != w->end_room)
                return (1);
    return (0);
}

int check_start_end(lemin_t *w)
{
    int nb = 0;

    for (int i = 0; w->ways[i] != NULL; i++)
        if (w->ways[i][1] != NULL && w->ways[i][1] == w->end_room)
            nb++;
    if (nb > 1)
        return (1);
    return (0);
}

int end_way(room_t *room, lemin_t *w)
{
    for (int i = 0; room->link[i] != NULL; i++)
        if (room->link[i] == w->end_room)
            return (1);
    return (0);
}

void added_room(lemin_t *w, room_t *room, room_t **way)
{
    int depth = 0;

    if (room == w->end_room)
        return;
    for (; way[depth] != NULL; depth++);
    if (room != w->start_room && end_way(room, w))
        way[depth] = w->end_room;
    for (int i = 0; room->link[i] != NULL && way[depth] == NULL ; i++)
        if (already_exist(w->ways, room->link[i], w) == 0) {
            way[depth] = room->link[i];
            way[depth+1] = NULL;
            added_room(w, room->link[i], way);
            if (check_start_end(w))
                way[depth] = NULL;
        }
    if (way[depth] == NULL) {
        way[depth-1] = NULL;
        return;
    }
}

void create_way(lemin_t *w)
{
    int nbr_link = (nb_link(w->start_room) < nb_link(w->end_room))
        ? nb_link(w->start_room) : nb_link(w->end_room);

    w->ways = malloc(sizeof(room_t **) * (nbr_link + 1));
    for (int i = 0; i != nbr_link; i++) {
        w->ways[i] = malloc(sizeof(room_t *) * (nb_room(w) + 1));
        w->ways[i][0] = w->start_room;
        w->ways[i][1] = NULL;
    }
    for (int i = 0; i != nbr_link && w->ways[i][0] != NULL; i++) {
        added_room(w, w->start_room, w->ways[i]);
        if (w->ways[i][0] == NULL) {
            w->ways[i] = NULL;
            return;
        }
    }
}
