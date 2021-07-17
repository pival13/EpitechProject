/*
** EPITECH PROJECT, 2019
** main_menu.c
** File description:
** main menu
*/

#include "my.h"

int events_buttons_mm_2(rpg_t *w)
{
    static int color[3] = {50, 50, 50};
    int fd;

    if (click_button(w->cursor, w->mm->buttons[5], w->event) && \
w->mm->play_mode && check_save() == 1) {
        fd = open(".sav", O_WRONLY | O_TRUNC);
        close(fd);
        reset_time(w->mm->deleted->time_anim, w->clock);
    }
    if (click_button(w->cursor, w->mm->title, w->event) == 1) {
        mod_color(w->mm->bgd->sprite, color[0], color[1], color[2]);
        color[0] = rand() % 205 + 50;
        color[1] = rand() % 205 + 50;
        color[2] = rand() % 205 + 50;
    }
    return (0);
}

int events_buttons_main_menu(rpg_t *w)
{
    if (click_button(w->cursor, w->mm->buttons[4], w->event) && \
w->mm->play_mode) {
        w->mm->play_mode = 0;
        change_page(w, SAVE);
        return (0);
    }
    if (click_button(w->cursor, w->mm->buttons[PLAY], w->event) && \
!w->mm->play_mode) {
        w->mm->play_mode = 1;
        reset_time(w->mm->click_delay, w->clock);
    }
    if (click_button(w->cursor, w->mm->buttons[SETTINGS], w->event) && \
!w->mm->play_mode)
        change_page(w, SETT);
    if (click_button(w->cursor, w->mm->buttons[QUIT], w->event) && \
!w->mm->play_mode)
        sfRenderWindow_close(w->win);
    return (events_buttons_mm_2(w));
}

int events_main_menu(rpg_t *w)
{
    if (get_time(w->mm->click_delay, w->clock) < 0.1)
        return (0);
    if (click_button(w->cursor, w->mm->buttons[6], w->event) && \
w->mm->play_mode) {
        w->mm->play_mode = 0;
        reset_time(w->mm->click_delay, w->clock);
    }
    if (click_button(w->cursor, w->mm->buttons[3], w->event) && \
w->mm->play_mode && check_save()) {
        w->mm->play_mode = 0;
        load_save(w);
        complete_players(w);
        change_page(w, MAP);
        return (0);
    }
    if ((click_button(w->cursor, w->mm->buttons[3], w->event) ||
        click_button(w->cursor, w->mm->buttons[5], w->event)) &&
        w->mm->play_mode == 1 && check_save() == 0)
        reset_time(w->mm->no_save->time_anim, w->clock);
    return (events_buttons_main_menu(w));
}

void page_main_menu(rpg_t *w)
{
    for (int i = 0; w->musics[i] != NULL; i++)
        if (i != 0 && sfMusic_getStatus(w->musics[i]) == sfPlaying) {
            sfMusic_stop(w->musics[i]);
            sfMusic_play(w->musics[0]);
        }
    if (w->key_mode == M_MODE)
        events_main_menu(w);
    key_cursor_main_menu(w);
    animation_buttons_mm(w);
    draw_main_menu(w);
}
