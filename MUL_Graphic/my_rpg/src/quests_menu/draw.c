/*
** EPITECH PROJECT, 2019
** draw.c
** File description:
** draw quests menu
*/

#include "my.h"

void draw_quests_menu(rpg_t *w)
{
    draw_sprite(w->win, w->qm->bgd->sprite);
    draw_sprite(w->win, w->qm->switch_name_buttons[0]->sprite);
    draw_sprite(w->win, w->qm->switch_name_buttons[1]->sprite);
    draw_sftext(w->win, w->qm->quests_name[0]->text);
    draw_sftext(w->win, w->qm->quests_name[1]->text);
    draw_sftext(w->win, w->qm->quests_name[2]->text);
    draw_sftext(w->win, w->qm->desc->text);
    draw_sftext(w->win, w->qm->gold->text);
    draw_sftext(w->win, w->qm->exp->text);
    draw_sftext(w->win, w->qm->status->text);
    draw_sftext(w->win, w->qm->item->text);
    draw_sprite(w->win, w->qm->title->sprite);
    draw_sprite(w->win, w->qm->return_button->sprite);
}
