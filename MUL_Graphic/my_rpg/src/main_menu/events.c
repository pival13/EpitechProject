/*
** EPITECH PROJECT, 2019
** events.c
** File description:
** events mm funcs
*/

#include "my.h"

int key_cursor_mm_3(rpg_t *w)
{
    int fd;

    if (w->mm->key_pos == 2 && w->mm->play_mode && KEY_I()) {
        fd = open(".sav", O_WRONLY | O_TRUNC);
        close(fd);
        reset_time(w->mm->deleted->time_anim, w->clock);
    }
    return (0);
}

int key_cursor_main_menu_interactions2(rpg_t *w)
{
    if (w->mm->key_pos == 1 && w->mm->play_mode == 1 && KEY_I()) {
        w->mm->play_mode = 0;
        change_page(w, SAVE);
        return (0);
    }
    if (w->mm->key_pos == 0 && w->mm->play_mode == 0 && KEY_I()) {
        w->mm->play_mode = 1;
        reset_time(w->mm->click_delay, w->clock);
        return (0);
    }
    if (w->mm->key_pos == 1 && w->mm->play_mode == 0 && KEY_I()) {
        change_page(w, SETT);
        return (0);
    }
    if (w->mm->key_pos == 2 && w->mm->play_mode == 0 && KEY_I()) {
        sfRenderWindow_close(w->win);
        return (0);
    }
    return (key_cursor_mm_3(w));
}

int key_cursor_main_menu_interactions(rpg_t *w)
{
    if (w->mm->key_pos == 3 && w->mm->play_mode == 1 && KEY_I()) {
        w->mm->play_mode = 0;
        reset_time(w->mm->click_delay, w->clock);
        return (0);
    }
    if (w->mm->key_pos == 0 && w->mm->play_mode == 1 && KEY_I() && check_\
save()) {
        w->mm->play_mode = 0;
        load_save(w);
        complete_players(w);
        change_page(w, MAP);
        return (0);
    }
    if (w->mm->key_pos == 0 && w->mm->play_mode == 1 && KEY_I()
        && check_save() == 0)
        reset_time(w->mm->no_save->time_anim, w->clock);
    key_cursor_main_menu_interactions2(w);
    return (0);
}

void key_cursor_main_menu(rpg_t *w)
{
    (KEY_Z()) ? (w->mm->key_pos -= 1) : (0);
    (KEY_S()) ? (w->mm->key_pos += 1) : (0);
    (w->mm->key_pos < 0 && w->mm->play_mode == 0) ? (w->mm->key_pos = 2) : (0);
    (w->mm->key_pos < 0 && w->mm->play_mode == 1) ? (w->mm->key_pos = 3) : (0);
    (w->mm->key_pos > 2 && w->mm->play_mode == 0) ? (w->mm->key_pos = 0) : (0);
    (w->mm->play_mode == 1 && KEY_D()) ? (w->mm->key_pos = 3) : (0);
    (w->mm->play_mode == 1 && KEY_Q()) ? (w->mm->key_pos = 0) : (0);
    (w->mm->key_pos > 3 && w->mm->play_mode == 1) ? (w->mm->key_pos = 0) : (0);
    if (w->key_mode == K_MODE)
        key_cursor_main_menu_interactions(w);
}
