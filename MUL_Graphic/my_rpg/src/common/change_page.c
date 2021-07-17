/*
** EPITECH PROJECT, 2019
** change_page.c
** File description:
** change page
*/

#include "my.h"

void change_page(rpg_t *w, int page)
{
    w->old_page = w->page;
    w->page = page;
    if (page == QM)
        load_qm(w);
    sfMusic_play(w->sounds[S_PAGE]);
}

void change_page_back(rpg_t *w)
{
    int mem = w->old_page;

    if (w->page == MENU && w->mm->play_mode == 1) {
        w->mm->play_mode = 0;
        return;
    } else if (w->page == MENU) {
        sfRenderWindow_close(w->win);
    }
    sfMusic_play(w->sounds[S_PAGE]);
    (w->old_page == QM) ? (load_qm(w)) : (0);
    if (w->page != FIGHT) {
        w->old_page = w->page;
        if (w->page == SETT || w->page == SAVE)
            w->page = mem;
        else
            w->page = MAP;
    }
}
