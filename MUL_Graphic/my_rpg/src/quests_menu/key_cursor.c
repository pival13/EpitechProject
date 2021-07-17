/*
** EPITECH PROJECT, 2019
** key_cursor.c
** File description:
** key cursor events
*/

#include "my.h"

int key_cursor_qm_interactions2(rpg_t *w)
{
    if (w->qm->key_pos == 0 && KEY_D()) {
        change_title_qm_right(w);
        return (0);
    }
    if (w->qm->key_pos == 0 && KEY_Q()) {
        change_title_qm_left(w);
        return (0);
    }
    return (0);
}

int key_cursor_qm_interactions(rpg_t *w)
{
    if (w->qm->key_pos == 1 && KEY_I()) {
        change_page_back(w);
        return (0);
    }
    key_cursor_qm_interactions2(w);
    return (0);
}

void key_cursor_qm(rpg_t *w)
{
    if (w->key_mode == K_MODE) {
        key_cursor_qm_interactions(w);
        (KEY_Z()) ? (w->qm->key_pos -= 1) : (0);
        (KEY_S()) ? (w->qm->key_pos += 1) : (0);
        (w->qm->key_pos < 0) ? (w->qm->key_pos = 1) : (0);
        (w->qm->key_pos > 1) ? (w->qm->key_pos = 0) : (0);
    }
}
