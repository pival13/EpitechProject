/*
** EPITECH PROJECT, 2019
** create_qm_struct.c
** File description:
** create qm struct
*/

#include "my.h"

void configure_qm_titles(quest_m_t *qm, sfClock *clock)
{
    sfColor color = {228, 142, 21, 255};

    obj_set_position_text(qm->quests_name[0], 1920 / 2 - 530, 210);
    obj_set_position_text(qm->quests_name[1], 1920 / 2 - 140, 210);
    obj_set_position_text(qm->quests_name[2], 1920 / 2 + 250, 210);
    sfText_setColor(qm->quests_name[0]->text, color);
    sfText_setColor(qm->quests_name[1]->text, color);
    sfText_setColor(qm->quests_name[2]->text, color);
    sfText_setCharacterSize(qm->quests_name[0]->text, 30);
    sfText_setCharacterSize(qm->quests_name[1]->text, 30);
    sfText_setCharacterSize(qm->quests_name[2]->text, 30);
    create_desc_qm(qm, clock);
}

void create_qm_struct3(quest_m_t *qm, sfClock *clock, sfTexture **textures)
{
    qm->switch_name_buttons[0] = create_obj_t_sprite
    (clock, NULL, textures[BLEFT_QM]);
    obj_set_position(qm->switch_name_buttons[0], 1920 / 2 - 620, 240);
    qm->switch_name_buttons[1] = create_obj_t_sprite
    (clock, NULL, textures[BRIGHT_QM]);
    obj_set_position(qm->switch_name_buttons[1], 1920 / 2 + 630, 240);
    qm->title_pos = 0;
    configure_qm_titles(qm, clock);
}

void create_qm_struct2(quest_m_t *qm, sfClock *clock, sfTexture **textures)
{
    qm->bgd = create_obj_t_sprite
    (clock, NULL, textures[BGD_QM]);
    qm->bgd->origin.x = 0;
    qm->bgd->origin.y = 0;
    sfSprite_setOrigin(qm->bgd->sprite, qm->bgd->origin);
    mod_scale(qm->bgd, 2);
    qm->title = create_obj_t_sprite
    (clock, NULL, textures[TITLE_QM]);
    obj_set_position(qm->title, 1920 / 2, 50);
    mod_scale(qm->title, 1.5);
    qm->click_delay = create_time_obj(clock);
    create_qm_struct3(qm, clock, textures);
}

quest_m_t *create_quest_menu_struct(sfClock *clock, sfTexture **textures)
{
    quest_m_t *qm = malloc(sizeof(quest_m_t));

    qm->switch_buttons[0] = create_obj_t_sprite
    (clock, NULL, textures[BLEFT_QM]);
    obj_set_position(qm->switch_buttons[0], 1920 / 2 - 250, 50);
    qm->switch_buttons[1] = create_obj_t_sprite
    (clock, NULL, textures[BRIGHT_QM]);
    obj_set_position(qm->switch_buttons[1], 1920 / 2 + 250, 50);
    qm->return_button = create_obj_t_sprite
    (clock, NULL, textures[RETURN2]);
    obj_set_position(qm->return_button, 1920 - 145, 975);
    for (int i = 0; i <= 2; i++)
        qm->quests_name[i] = create_obj_t_text
        (clock, "Nom Xd", "data/fonts/CELT.TTF");
    create_qm_struct2(qm, clock, textures);
    qm->key_pos = 0;
    return (qm);
}

void destroy_quest_menu_struct(quest_m_t *qm)
{
    destroy_obj_t(qm->bgd);
    destroy_obj_t(qm->switch_buttons[0]);
    destroy_obj_t(qm->switch_buttons[1]);
    destroy_obj_t(qm->switch_name_buttons[0]);
    destroy_obj_t(qm->switch_name_buttons[1]);
    destroy_obj_t(qm->return_button);
    destroy_obj_t(qm->desc);
    destroy_obj_t(qm->gold);
    destroy_obj_t(qm->exp);
    destroy_obj_t(qm->status);
    destroy_obj_t(qm->item);
    destroy_obj_t(qm->title);
    for (int i = 0; i <= 2; i++)
        destroy_obj_t(qm->quests_name[i]);
    destroy_time_obj(qm->click_delay);
    free(qm);
}
