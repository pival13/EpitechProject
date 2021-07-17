/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of my_rpg
*/

#include "my.h"

void key_mode_set(rpg_t *w)
{
    if (w->event.type == sfEvtMouseMoved)
        w->key_mode = M_MODE;
    if (KEY_Q() || KEY_D() || KEY_Z() || KEY_S()) {
        w->key_mode = K_MODE;
    }
    if (KEY_I()) {
        w->key_mode = K_MODE;
    }
}

void init_window(rpg_t *w)
{
    sfRenderWindow_clear(w->win, sfWhite);
    sfRenderWindow_pollEvent(w->win, &w->event);
    key_mode_set(w);
    mouse_follow(w);
}

void init_next_whil(rpg_t *w)
{
    if (w->key_mode == M_MODE)
        sfRenderWindow_drawSprite(w->win, w->cursor->sprite, NULL);
    sfRenderWindow_display(w->win);
    (KEY_R(sfKeyEscape)) ? (change_page_back(w)) : (0);
    if (w->event.type == sfEvtMouseButtonReleased) {
        w->event.type = sfEvtMouseMoved;
        sfMusic_play(w->sounds[S_INTERACTION]);
    }
    if (w->event.type == sfEvtClosed)
        sfRenderWindow_close(w->win);
    if (w->event.type == sfEvtKeyReleased) {
        w->event.type = 1;
        sfMusic_play(w->sounds[S_INTERACTION]);
    }
}

int main(int n, char **arg)
{
    rpg_t *w = create_rpg_struct();
    void (*pages[])(rpg_t *) = {page_main_menu, character_menu, page_world,
    page_settings, page_create_save, page_quests_menu, fight, page_intro};

    if (w == NULL)
        return (84);
    if (n != 1 || arg[1] != NULL)
        return (destroy_rpg_struct(w));
    sfMusic_play(w->musics[0]);
    while (sfRenderWindow_isOpen(w->win)) {
        init_window(w);
        for (int i = 0; w->qm->quests[i].name != NULL; i++)
            (!w->qm->quests[i].completed) ?
                (w->qm->quests[i].funct(w, &w->qm->quests[i])) : (0);
        (*pages[w->page])(w);
        init_next_whil(w);
    }
    destroy_rpg_struct(w);
    return (0);
}
