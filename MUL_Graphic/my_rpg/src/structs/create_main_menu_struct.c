/*
** EPITECH PROJECT, 2019
** create_main_menu_struct.c
** File description:
** create main menu struct
*/

#include "my.h"

void create_mm_buttons_3(main_menu_t *mm, sfClock *clock, sfTexture **textures)
{
    mm->deleted = create_obj_t_sprite
    (clock, NULL, textures[DELETEDMM]);
    mm->no_save = create_obj_t_sprite
    (clock, NULL, textures[NOSAVEMM]);
    obj_set_position(mm->no_save, 1920 / 2, 1080 / 2);
    obj_set_position(mm->deleted, 1920 / 2, 1080 / 2);
    mm->no_save->time_anim->seconds = 2;
    mm->deleted->time_anim->seconds = 2;
}

void create_mm_buttons_2(main_menu_t *mm, sfClock *clock, sfTexture **textures)
{
    mm->buttons[3] = create_obj_t_sprite
    (clock, NULL, textures[LOADMM]);
    obj_set_position(mm->buttons[3], 960, 350);
    mm->buttons[4] = create_obj_t_sprite
    (clock, NULL, textures[CREATEMM]);
    obj_set_position(mm->buttons[4], 960, 600);
    mm->buttons[5] = create_obj_t_sprite
    (clock, NULL, textures[DELETEMM]);
    obj_set_position(mm->buttons[5], 960, 850);
    mm->buttons[6] = create_obj_t_sprite
    (clock, NULL, textures[RETURNMM]);
    obj_set_position(mm->buttons[6], 1600, 850);
    mm->title = create_obj_t_sprite
    (clock, NULL, textures[TITLEMM]);
    obj_set_position(mm->title, 960, 125);
    cut_animation(mm->title, 7, 1);
    mm->key_cursor = create_key_cursor(clock);
    mm->key_pos = 0;
    create_mm_buttons_3(mm, clock, textures);
}

main_menu_t *create_main_menu_struct(sfClock *clock, sfTexture **textures)
{
    main_menu_t *mm = malloc(sizeof(main_menu_t));

    mm->play_mode = 0;
    mm->buttons[PLAY] = create_obj_t_sprite
    (clock, NULL, textures[PLAYMM]);
    obj_set_position(mm->buttons[PLAY], 960, 350);
    mm->buttons[SETTINGS] = create_obj_t_sprite
    (clock, NULL, textures[SETTMM]);
    obj_set_position(mm->buttons[SETTINGS], 960, 600);
    mm->buttons[QUIT] = create_obj_t_sprite
    (clock, NULL, textures[QUITMM]);
    obj_set_position(mm->buttons[QUIT], 960, 850);
    mm->bgd = create_obj_t_sprite
    (clock, NULL, textures[BGDMM]);
    mm->bgd->origin.x = mm->bgd->rect.width / 2;
    mm->bgd->origin.y = 0;
    sfSprite_setOrigin(mm->bgd->sprite, mm->bgd->origin);
    mm->click_delay = create_time_obj(clock);
    create_mm_buttons_2(mm, clock, textures);
    return (mm);
}

void destroy_main_menu_struct(main_menu_t *mm)
{
    for (int i = 0; i < 7; i++)
        destroy_obj_t(mm->buttons[i]);
    destroy_obj_t(mm->title);
    destroy_obj_t(mm->bgd);
    destroy_time_obj(mm->click_delay);
    free(mm);
}
