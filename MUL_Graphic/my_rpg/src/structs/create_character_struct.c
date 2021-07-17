/*
** EPITECH PROJECT, 2019
** rpg.h
** File description:
** header of my_rpg
*/

#include "my.h"

void create_character_ingame2(sfClock *cl, sfTexture **te, character_t *ch)
{
    ch->ogref = create_obj_t_sprite(cl, NULL, te[OGREF]);
    obj_set_position(ch->ogref, 275, 700);
    ch->deamon = create_obj_t_sprite(cl, NULL, te[DEMONH]);
    obj_set_position(ch->deamon, 275, 700);
    ch->deamonf = create_obj_t_sprite(cl, NULL, te[DEMONF]);
    obj_set_position(ch->deamonf, 275, 700);
    ch->character = create_obj_t_sprite(cl, NULL, te[TITLE_CH]);
    obj_set_position(ch->character, 950, 220);
    ch->button_right = create_obj_t_sprite(cl, NULL, te[BRIGHT_QM]);
    obj_set_position(ch->button_right, 1220, 220);
    ch->button_left = create_obj_t_sprite(cl, NULL, te[BLEFT_QM]);
    obj_set_position(ch->button_left, 675, 220);
}

character_t *create_character_ingame(sfClock *clock, sfTexture **textures)
{
    character_t *ch = malloc(sizeof(character_t));

    ch->bgd = create_obj_t_sprite(clock, NULL, textures[BGD_CH]);
    obj_set_position(ch->bgd, 960, 540);
    ch->elf = create_obj_t_sprite(clock, NULL, textures[ELFH]);
    obj_set_position(ch->elf, 275, 700);
    ch->elff = create_obj_t_sprite(clock, NULL, textures[ELFF]);
    obj_set_position(ch->elff, 275, 700);
    ch->human = create_obj_t_sprite(clock, NULL, textures[HUMANH]);
    obj_set_position(ch->human, 275, 700);
    ch->humanf = create_obj_t_sprite(clock, NULL, textures[HUMANF]);
    obj_set_position(ch->humanf, 275, 700);
    ch->naim = create_obj_t_sprite(clock, NULL, textures[NAINH]);
    obj_set_position(ch->naim, 275, 700);
    ch->naimf = create_obj_t_sprite(clock, NULL, textures[NAINF]);
    obj_set_position(ch->naimf, 275, 700);
    ch->ogre = create_obj_t_sprite(clock, NULL, textures[OGREH]);
    obj_set_position(ch->ogre, 275, 700);
    create_character_ingame2(clock, textures, ch);
    return (ch);
}

void destroy_character_texture(character_t *ch)
{
    destroy_obj_t(ch->bgd);
    destroy_obj_t(ch->elf);
    destroy_obj_t(ch->elff);
    destroy_obj_t(ch->human);
    destroy_obj_t(ch->humanf);
    destroy_obj_t(ch->naim);
    destroy_obj_t(ch->naimf);
    destroy_obj_t(ch->ogre);
    destroy_obj_t(ch->ogref);
    destroy_obj_t(ch->deamon);
    destroy_obj_t(ch->deamonf);
    destroy_obj_t(ch->button_right);
    destroy_obj_t(ch->button_left);
}
