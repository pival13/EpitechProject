/*
** EPITECH PROJECT, 2019
** events.c
** File description:
** events intro
*/

#include "my.h"

void animation_bgd_intro(rpg_t *w)
{
    static sfColor color = {255, 255, 255, 250};

    get_time(w->intro->bgd->time_move, w->clock);
    obj_move(w->intro->bgd, 150 * w->intro->bgd->time_move->seconds, 0);
    if (w->intro->bgd->pos.x >= w->intro->bgd->rect.width / 2)
        obj_set_position(w->intro->bgd, 0, 0);
    reset_time(w->intro->bgd->time_move, w->clock);
    get_time(w->intro->bgd2->time_move, w->clock);
    obj_move(w->intro->bgd2, 150 * w->intro->bgd2->time_move->seconds, 0);
    if (w->intro->bgd2->pos.x >= w->intro->bgd->rect.width / 2)
        obj_set_position(w->intro->bgd2, 0, 0);
    reset_time(w->intro->bgd2->time_move, w->clock);
    get_time(w->intro->bgd->time_anim, w->clock);
    if (w->intro->bgd->time_anim->seconds > 0.01 && color.a > 0) {
        color.a -= 1;
        reset_time(w->intro->bgd->time_anim, w->clock);
    }
    sfSprite_setColor(w->intro->bgd->sprite, color);
}

void animation_charles(rpg_t *w)
{
    static int sens = 1;

    get_time(w->intro->narrator->time_move, w->clock);
    get_time(w->intro->narrator->time_anim, w->clock);
    (w->intro->speaking == 1) ? (set_anim_sprite(w->intro->narrator, 1, 0)) :
    (set_anim_sprite(w->intro->narrator, 1, 1));
    if (w->intro->narrator->time_anim->seconds > 0.16) {
        anim_sprite(w->intro->narrator, 0, 1);
        reset_time(w->intro->narrator->time_anim, w->clock);
    }
    if (w->intro->narrator->time_move->seconds >= 0.005) {
        sfSprite_rotate(w->intro->narrator->sprite, 0.2 * sens);
        reset_time(w->intro->narrator->time_move, w->clock);
        if (SANG(w->intro->narrator->sprite) < 330 &&
            SANG(w->intro->narrator->sprite) > 30) {
            sens *= -1;
            sfSprite_rotate(w->intro->narrator->sprite, 0.2 * sens);
        }
    }
}

void events_dialogue_intro(rpg_t *w)
{
    static time_obj *time = NULL;

    (time == NULL) ? (time = create_time_obj(w->clock)) : (0);
    get_time(time, w->clock);
    if ((KEY_I() || (w->event.mouseButton.button == sfMouseLeft &&
        w->event.type == sfEvtMouseButtonReleased)) && time->seconds > 0.2) {
        w->intro->speaking = 0;
        reset_time(time, w->clock);
    }
    set_invisible(w->intro->key_cursor->sprite);
}

void events_choices_intro(rpg_t *w)
{
    static time_obj *time = NULL;

    (time == NULL) ? (time = create_time_obj(w->clock)) : (0);
    get_time(time, w->clock);
    if (KEY_I() && time->seconds > 0.2) {
        w->intro->speaking = 1;
        w->intro->step += 1;
        reset_time(time, w->clock);
    }
    if ((click_button_text(w->cursor, w->intro->choices[0], w->event) ||
        click_button_text(w->cursor, w->intro->choices[1], w->event) ||
        click_button_text(w->cursor, w->intro->choices[2], w->event))
        && time->seconds > 0.2) {
        w->intro->speaking = 1;
        w->intro->step += 1;
        reset_time(time, w->clock);
    }
    events_choices_intro_expanded(w);
}

void events_intro(rpg_t *w)
{
    static int i = 0;

    if (w->intro->speaking == 1)
        events_dialogue_intro(w);
    else
        events_choices_intro(w);
    if (i == 0) {
        reset_time(w->intro->bgd->time_anim, w->clock);
        w->intro->speaking = 1;
        i = 1;
    }
    animation_charles(w);
    animation_bgd_intro(w);
    dialogue_intro(w);
    if (w->intro->speaking == 1) {
        edit_text_str(w->intro->choices[0], "");
        edit_text_str(w->intro->choices[1], "");
        edit_text_str(w->intro->choices[2], "");
    } else
        edit_text_str(w->intro->point, "");
}
