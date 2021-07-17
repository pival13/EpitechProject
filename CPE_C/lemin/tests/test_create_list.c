/*
** EPITECH PROJECT, 2019
** test_create_list
** File description:
** test the create list function
*/

#include <criterion/criterion.h>
#include "my.h"
#include "lemin.h"

Test(create_list, test_link)
{
    char *name[5] = {strdup("corridor 1 1"), strdup("kitchen 1 2"),
                    strdup("bedroom 2 2"), strdup("bathroom 1 3"), NULL};
    char *link[9] = {"corridor-kitchen", "corridor-bedroom", "corridor-b\
athroom", "bedroom-bathroom", "corridor-corridor", "corridor-toilet", "c\
orridor-kitchen", NULL};
    room_t *room = create_room(name, link);

    cr_assert_null(room->link[3]);
}

Test(create_list, changing_room)
{
    char *name[5] = {strdup("corridor 1 1"), strdup("kitchen 1 2"),
                    strdup("bedroom 2 2"), strdup("bathroom 1 3"), NULL};
    char *link[9] = {"corridor-kitchen", "corridor-bedroom", "corridor-b\
athroom", "bedroom-bathroom", "kitchen-kitchen", "bedroom-toilet", "corr\
idor-kitchen", NULL};
    room_t *room = create_room(name, link);

    cr_assert_str_eq(room->name, "corridor");
    cr_assert_eq(room->pos[0], 1);
    cr_assert_eq(room->pos[1], 1);
    room = room->link[1];
    cr_assert_eq(room->pos[0], 2);
    cr_assert_eq(room->pos[0], 2);
    cr_assert_str_eq(room->name, "bedroom");
    cr_assert_str_eq(room->link[0]->link[0]->name, "kitchen");
    cr_assert_str_eq(room->link[1]->name, "bathroom");
    cr_assert_str_eq(room->link[1]->name, room->link[0]->link[2]->name);
}

Test(find_room, search_a_room)
{
    char *name[5] = {strdup("corridor 1 1"), strdup("kitchen 1 2"),
                    strdup("bedroom 2 2"), strdup("bathroom 1 3"), NULL};
    char *link[9] = {"corridor-kitchen", "corridor-bedroom", "corridor-b\
athroom", "bedroom-bathroom", "kitchen-kitchen", "bedroom-toilet", "corr\
idor-kitchen", NULL};
    room_t *room = create_room(name, link);

    cr_assert_str_eq(find_room(room, "bathroom", 0)->name, "bathroom");
    cr_assert_str_eq(find_room(room->link[0], "bedroom", 0)->name, "bedroom");
    cr_assert_str_eq(find_room(room, "corridor", 0)->name, "corridor");
    cr_assert_null(find_room(room, "kitchen", 20));
}
