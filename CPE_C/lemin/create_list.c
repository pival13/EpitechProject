/*
** EPITECH PROJECT, 2019
** create_list
** File description:
** create the list
*/

#include "lemin.h"
#include "my.h"
#include <stdlib.h>

int number_link(char **link, char *name)
{
    int nb_link = 0;

    for (int i = 0; link[i] != NULL; i++)
        if (is_word(link[i], name))
            nb_link++;
    return (nb_link);
}

void linked_two_room(room_t *room1, room_t *room2)
{
    int l1 = 0;
    int l2 = 0;
    int i = 0;

    for (; room1->link[i] != NULL && my_strcmp(room1->\
link[i]->name, room2->name) != 0; i++);
    if (room1->link[i] != NULL)
        return;
    for (; room1->link[l1] != NULL; l1++);
    for (; room2->link[l2] != NULL; l2++);
    room1->link[l1] = room2;
    room1->link[l1+1] = NULL;
    room2->link[l2] = room1;
    room2->link[l2+1] = NULL;
}

void linked_room(room_t *r, char **link)
{
    room_t *room1 = NULL;
    room_t *room2 = NULL;

    for (int j = 0; link[j] != NULL; j++) {
        for (int i = 0; r[i].name != NULL; i++) {
            if (room1 != NULL && is_word(link[j], r[i].name))
                room2 = &r[i];
            if (room1 == NULL && is_word(link[j], r[i].name))
                room1 = &r[i];
        }
        if (room1 != NULL && room2 != NULL) {
            linked_two_room(room1, room2);
        }
        room1 = NULL;
        room2 = NULL;
    }
}

void add_name_pos(room_t *room, char *name)
{
    int i = 0;
    int mem;

    for (; is_alphanum(name[i]); i++);
    room->name = malloc(sizeof(char *) * (i));
    for (int j = 0; j != i; j++) room->name[j] = name[j];
    room->name[i] = '\0';
    i++;
    room->pos[0] = my_getnbr(&name[i]);
    for (; name[i] != ' '; i++);
    i++;
    room->pos[1] = my_getnbr(&name[i]);
}

room_t *create_room(char **name, char **link)
{
    room_t *room = malloc(sizeof(room_t) * (nb_row(name)-nb_row(link)+1));

    if (room == NULL || name == NULL || link == NULL) return (NULL);
    for (int i = 0; is_room(name[i]); i++) {
        add_name_pos(&room[i], name[i]);
        room[i].link = malloc(sizeof(room_t *) *
        (number_link(link, room[i].name)+1));
        if (room[i].link == NULL) return (NULL);
        room[i].ant = 0;
        room[i].link[0] = NULL;
        room[i+1].name = NULL;
    }
    linked_room(room, link);
    return (&room[0]);
}
