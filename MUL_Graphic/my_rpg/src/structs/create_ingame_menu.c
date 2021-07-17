/*
** EPITECH PROJECT, 2019
** ingame menue
** File description:
** display ingame menue
*/

#include "my.h"

void create_ingame_menu_struct3(sfClock *clock, sfTexture **textures, \
ingame_t *ig)
{
    ig->shop[0] = create_obj_t_sprite
    (clock, NULL, textures[DEMON_IG]);
    ig->shop[1] = create_obj_t_sprite
    (clock, NULL, textures[DWARF_IG]);
    ig->shop[2] = create_obj_t_sprite
    (clock, NULL, textures[ELF_IG]);
    ig->shop[3] = create_obj_t_sprite
    (clock, NULL, textures[HUMAN_IG]);
    ig->shop[4] = create_obj_t_sprite
    (clock, NULL, textures[OGRE_IG]);
    obj_set_position(ig->shop[0], 1450, 200);
    obj_set_position(ig->shop[1], 1450, 500);
    obj_set_position(ig->shop[2], 1750, 200);
    obj_set_position(ig->shop[3], 1750, 500);
    obj_set_position(ig->shop[4], 1600, 800);
}

void create_ingame_menu_struct2(sfClock *clock, sfTexture **textures, \
ingame_t *ig)
{
    ig->buttons[QUIT_IG] = create_obj_t_sprite
    (clock, NULL, textures[QUIT_B_IG]);
    obj_set_position(ig->buttons[QUIT_IG], 960, 820);
    ig->bgd = create_obj_t_sprite
    (clock, NULL, textures[PANEL_IG]);
    obj_set_position(ig->bgd, 1920 / 2, 1080 / 2);
    ig->message_save = create_obj_t_sprite
    (clock, NULL, textures[MESSAGE_SAVE_IG]);
    obj_set_position(ig->message_save, 960, 540);
    ig->message_save->time_anim->seconds = 2;
    create_ingame_menu_struct3(clock, textures, ig);
    ig->bought = create_obj_t_sprite
    (clock, NULL, textures[BOUGHT]);
    obj_set_position(ig->bought, 960, 540);
    ig->no_money = create_obj_t_sprite
    (clock, NULL, textures[NOMONEY]);
    obj_set_position(ig->no_money, 960, 540);
}

ingame_t *create_ingame_menu_struct(sfClock *clock, sfTexture **textures)
{
    ingame_t *ig = malloc(sizeof(ingame_t));

    ig->buttons[SETTINGS_IG] = create_obj_t_sprite
    (clock, NULL, textures[SETT_IG]);
    obj_set_position(ig->buttons[SETTINGS_IG], 960, 680);
    ig->buttons[INVENTORY] = create_obj_t_sprite
    (clock, NULL, textures[CH_IG]);
    obj_set_position(ig->buttons[INVENTORY], 960, 260);
    ig->buttons[QUEST] = create_obj_t_sprite
    (clock, NULL, textures[QUESTS_B_IG]);
    obj_set_position(ig->buttons[QUEST], 960, 400);
    ig->buttons[SAVE_IG] = create_obj_t_sprite
    (clock, NULL, textures[SAV_IG]);
    obj_set_position(ig->buttons[SAVE_IG], 960, 540);
    create_ingame_menu_struct2(clock, textures, ig);
    ig->key_pos = 0;
    ig->key_pos2 = 0;
    return (ig);
}

void destroy_ingame_menu_struct(ingame_t *ig)
{
    for (int a = 0; a != 5; a++)
        destroy_obj_t(ig->buttons[a]);
    destroy_obj_t(ig->bgd);
    destroy_obj_t(ig->no_money);
    destroy_obj_t(ig->bought);
    free(ig);
}
