/*
** EPITECH PROJECT, 2019
** ways_possible.c
** File description:
** ways possible to go through
*/

#include "my.h"
#include <stdio.h>

room_t *create_ways_t3(room_t *start_room, int nb, lemin_t *w, int id)
{
    for (id = 0; w->ways[id] != NULL && way_finished(w->ways[id]) == 0; id++);
    if (start_room == w->end_room) {
        w->ways[id][nb] = -2;
        return (w->end_room);
    } else if (nb > 50)
        return (NULL);
}

void rewrite_w_ways(lemin_t *w, int id, int nb)
{
    for (int i = 0; i < nb; i++)
        w->ways[id][i] = w->ways[id-1][i];
}

room_t *create_ways_t2(room_t *start_room, int nb, lemin_t *w, char **mem)
{
    room_t *alt;
    int id = 0;

    start_room = create_ways_t3(start_room, nb, w, id);
    for (int i = 0; mem[i] != NULL; i++)
        if (mem[i] == NULL || mem[i+1] == NULL)
            mem[i] = name;
    for (int i = 0; start_room->link[i] != NULL; i++) {
        if (in_mem(start_room->link[i], mem) == 0)
            alt = create_ways_t2(start_room->link[i], nb + 1, w, mem);
        if (alt != NULL) {
            w->ways[id][nb] = i;
            (alt == w->end_room) ? (id++, rewrite_w_ways(w, id, nb)) : (0);
        }
    }
    return (alt);
}

int search_max_len(lemin_t *w)
{
    room_t **room = w->tab_room;
    int len = 0;

    for (int i = 0; room[i] != NULL; i++) {
        if (my_strlen(room[i]->name) > len)
            len = my_strlen(room[i]->name);
    }
    return (len);
}

int create_ways(lemin_t *w)
{
    room_t *room_manip = w->start_room;
    char **memory = malloc(sizeof(char *) * (my_pow(rooms_len(w), 2) + 1));
    int max_len = search_max_len(w);

    w->ways = malloc(sizeof(int *) * (my_pow(rooms_len(w), 2) + 1));
    for (int i = 0; i < my_pow(rooms_len(w), 2); i++) {
        w->ways[i] = malloc(sizeof(int) * (my_pow(rooms_len(w), 2)));
        w->ways[i+1] = NULL;
        memory[i] = NULL;
        for (int j = 0; j < my_pow(rooms_len(w), 2); j++)
            w->ways[i][j] = -1;
    }
    if (w->ways == NULL)
        return (84);
    create_ways_t2(w->start_room, 0, w, memory);
}
