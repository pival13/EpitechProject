/*
** EPITECH PROJECT, 2019
** create_intro_struct.c
** File description:
** create intro struct
*/

#include "my.h"

void read_intro_struct(intro_t *intro, sfClock *clock)
{
    intro->dialogue_tab = read_file("data/dialogue.data");
    intro->choices_tab = read_file("data/choices.data");
    edit_text(intro->dialogue, "", 100, 850);
    edit_text(intro->choices[0], "", 150, 70);
    edit_text(intro->choices[1], "", 150, 280);
    edit_text(intro->choices[2], "", 150, 480);
    intro->point = create_text("...", 150, intro->font);
    edit_text(intro->point, "...", 1730, 880);
    edit_text_color(intro->point, 255, 40, 43);
    intro->point_delay = create_time_obj(clock);
    intro->step = 0;
    edit_text_color(intro->dialogue, 29, 23, 20);
}

void place_intro_struct(intro_t *intro, sfClock *clock, sfTexture **te)
{
    intro->f_dialogue = create_obj_t_sprite
    (clock, NULL, te[DBOX_INT]);
    intro->f_choices = create_obj_t_sprite
    (clock, NULL, te[CHOICE_INT]);
    cut_animation(intro->narrator, 2, 2);
    intro->key_pos = 0;
    intro->end = 0;
    intro->bgd2->origin.x = intro->bgd2->rect.width / 2;
    intro->bgd2->origin.y = 0;
    intro->bgd->origin.x = intro->bgd->rect.width / 2;
    intro->bgd->origin.y = 0;
    sfSprite_setOrigin(intro->bgd->sprite, intro->bgd->origin);
    sfSprite_setOrigin(intro->bgd2->sprite, intro->bgd2->origin);
    obj_set_position(intro->narrator, 1920 / 4 * 3, 1080 / 6 * 2);
    mod_scale(intro->narrator, 1.5);
    obj_set_position(intro->f_dialogue, 1920 / 2, 1080 / 8 * 7);
    obj_set_position(intro->f_choices, 1920 / 10 * 2.2 + 50, 1080 / 3);
    set_invisible(intro->key_cursor->sprite);
    intro->speaking = 1;
    read_intro_struct(intro, clock);
}

intro_t *create_intro_struct(sfClock *clock, sfTexture **te)
{
    intro_t *intro = malloc(sizeof(intro_t));

    intro->font = sfFont_createFromFile("data/intro/intro_font.otf");
    intro->dialogue = create_text("Ah", 50, intro->font);
    for (int i = 0; i < 3; i++)
        intro->choices[i] = create_text("Ah", 50, intro->font);
    intro->key_cursor = create_obj_t_sprite
    (clock, NULL, te[ARROW_INT]);
    intro->bgd = create_obj_t_sprite
    (clock, NULL, te[BGDMM]);
    intro->bgd2 = create_obj_t_sprite
    (clock, NULL, te[BGD_INT]);
    intro->narrator = create_obj_t_sprite
    (clock, NULL, te[NARR_INT]);
    place_intro_struct(intro, clock, te);
    if (intro->dialogue_tab == NULL || intro->choices_tab == NULL) {
        my_dprintf(2, "dialogue.data/choices.data is/are bugged or missing.\n");
        return (NULL);
    }
    return (intro);
}

void destroy_intro_struct(intro_t *intro)
{
    destroy_obj_t(intro->bgd);
    destroy_obj_t(intro->bgd2);
    destroy_obj_t(intro->narrator);
    destroy_obj_t(intro->key_cursor);
    destroy_obj_t(intro->f_dialogue);
    destroy_obj_t(intro->f_choices);
    sfFont_destroy(intro->font);
    sfText_destroy(intro->dialogue);
    for (int i = 0; i < 3; i++)
        sfText_destroy(intro->choices[i]);
    for (int i = 0; intro->dialogue_tab[i] != NULL; i++)
        free(intro->dialogue_tab[i]);
    free(intro->dialogue_tab);
    for (int i = 0; intro->choices_tab[i] != NULL; i++)
        free(intro->choices_tab[i]);
    free(intro->choices_tab);
    sfText_destroy(intro->point);
    destroy_time_obj(intro->point_delay);
    free(intro);
}
