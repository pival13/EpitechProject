/*
** EPITECH PROJECT, 2019
** create_qm_struct_desc.c
** File description:
** create qm struct desc
*/

#include "my.h"

void position_desc_qm(quest_m_t *qm)
{
    sfColor color = {228, 142, 21 , 255};

    obj_set_position_text(qm->desc, 150, 450);
    obj_set_position_text(qm->gold, 150, 950);
    obj_set_position_text(qm->exp, 400, 950);
    obj_set_position_text(qm->status, 1230, 940);
    obj_set_position_text(qm->item, 150, 900);
    sfText_setCharacterSize(qm->desc->text, 25);
    sfText_setCharacterSize(qm->gold->text, 25);
    sfText_setCharacterSize(qm->exp->text, 25);
    sfText_setCharacterSize(qm->status->text, 35);
    sfText_setCharacterSize(qm->item->text, 25);
    sfText_setColor(qm->desc->text, color);
    sfText_setColor(qm->gold->text, color);
    sfText_setColor(qm->exp->text, color);
    sfText_setColor(qm->item->text, color);
    sfText_setColor(qm->status->text, color);
}

void create_desc_qm(quest_m_t *qm, sfClock *clock)
{
    qm->desc = create_obj_t_text
    (clock, "Description ah", "data/fonts/pieces.otf");
    qm->gold = create_obj_t_text
    (clock, "Gold : 100", "data/fonts/CELT.TTF");
    qm->exp = create_obj_t_text
    (clock, "EXP : 100", "data/fonts/CELT.TTF");
    qm->status = create_obj_t_text
    (clock, "Status : In Progress", "data/fonts/CELT.TTF");
    qm->item = create_obj_t_text
    (clock, "Objet : XDDDDDDDDDDDDd", "data/fonts/CELT.TTF");
    position_desc_qm(qm);
}
