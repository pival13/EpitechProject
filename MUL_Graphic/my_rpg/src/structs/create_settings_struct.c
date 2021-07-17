/*
** EPITECH PROJECT, 2019
** create_settings_struct.c
** File description:
** create settings struct
*/

#include "my.h"

void create_bars_settings(settings_t *sett, sfClock *cl, sfTexture **textures)
{
    int x = 600;
    int y[2] = {200, 500};

    sett->music_icon = create_obj_t_sprite(cl, NULL, textures[MUSICSETT]);
    cut_animation(sett->music_icon, 2, 1);
    obj_set_position(sett->music_icon, x, y[0]);
    sett->sound_icon = create_obj_t_sprite(cl, NULL, textures[SNDFXSETT]);
    cut_animation(sett->sound_icon, 2, 1);
    obj_set_position(sett->sound_icon, x, y[1]);
    x += 120;
    for (int i = 0; i < 10; i++, x += 70) {
        sett->sound_bar[i] = create_obj_t_sprite(cl, NULL, textures[BARSSETT]);
        sett->music_bar[i] = create_obj_t_sprite(cl, NULL, textures[BARSSETT]);
        obj_set_position(sett->music_bar[i], x, y[0]);
        obj_set_position(sett->sound_bar[i], x, y[1]);
        cut_animation(sett->sound_bar[i], 2, 1);
        cut_animation(sett->music_bar[i], 2, 1);
    }
    sett->return_button = create_obj_t_sprite(cl, NULL, textures[RETURNMM]);
    obj_set_position(sett->return_button, 1600, 850);
}

settings_t *create_settings_struct(sfClock *clock, sfTexture **textures)
{
    settings_t *sett = malloc(sizeof(settings_t));

    sett->sound_volume = 50;
    sett->music_volume = 50;
    sett->bgd = create_obj_t_sprite
    (clock, NULL, textures[BGDMM]);
    sett->bgd->origin.x = sett->bgd->rect.width / 2;
    sett->bgd->origin.y = 0;
    sfSprite_setOrigin(sett->bgd->sprite, sett->bgd->origin);
    create_bars_settings(sett, clock, textures);
    sett->key_cursor = create_key_cursor(clock);
    sett->key_pos = 0;
    return (sett);
}

void destroy_settings_struct(settings_t *sett)
{
    for (int i = 0; i < 10; i++) {
        destroy_obj_t(sett->music_bar[i]);
        destroy_obj_t(sett->sound_bar[i]);
    }
    destroy_obj_t(sett->sound_icon);
    destroy_obj_t(sett->music_icon);
    destroy_obj_t(sett->return_button);
    destroy_obj_t(sett->bgd);
    destroy_obj_t(sett->key_cursor);
    free(sett);
}
