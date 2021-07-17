/*
** EPITECH PROJECT, 2019
** page.c
** File description:
** page intro
*/

#include "my.h"

void page_intro(rpg_t *w)
{
    if (KEY_R(sfKeyEscape))
        page_create_save(w);
    events_intro(w);
    draw_intro(w);
}
