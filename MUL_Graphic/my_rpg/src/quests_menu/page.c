/*
** EPITECH PROJECT, 2019
** page.c
** File description:
** page quests menu
*/

#include "my.h"

void page_quests_menu(rpg_t *w)
{
    events_quests_menu(w);
    draw_quests_menu(w);
}
