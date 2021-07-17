/*
** EPITECH PROJECT, 2019
** menu
** File description:
** menu page
*/

#include <stdlib.h>
#include "csfml.h"

void change_color(text_t **t, int a)
{
    if (a == 0) {
        sfText_setColor(t[1]->text, sfCyan);
        sfText_setColor(t[2]->text, sfWhite);
        sfText_setColor(t[3]->text, sfWhite);
    } else if (a == 1) {
        sfText_setColor(t[1]->text, sfWhite);
        sfText_setColor(t[2]->text, sfCyan);
        sfText_setColor(t[3]->text, sfWhite);
    } else {
        sfText_setColor(t[1]->text, sfWhite);
        sfText_setColor(t[2]->text, sfWhite);
        sfText_setColor(t[3]->text, sfCyan);
    }
}

int menu_event(window_t *w, int a, object_t *back)
{
    if (sfRenderWindow_pollEvent(w->window, &w->event)) {
        if (w->event.type == sfEvtClosed)
            sfRenderWindow_close(w->window);
        if (w->event.type == sfEvtKeyPressed && w->event.key.code == sfKeyUp)
            a = (a+2) % 3;
        if (w->event.type == sfEvtKeyPressed && w->event.key.code == sfKeyDown)
            a = (a+1) % 3;
        if (w->event.type == sfEvtKeyPressed && w->event.key.code == sfKey\
Return) {
            if (a == 0)
                choose_level(w, back);
            else if (a == 1)
                how_to_play(w, back);
            else
                sfRenderWindow_close(w->window);
        }
    }
    return (a);
}

void menu(void)
{
    window_t *w = create_struct_window(800, 400, "my_runner", NULL);
    object_t *back = create_obj("sprite/menu.png", 1, 0, 0);
    int a = 0;
    text_t *t[4] = {create_text("My Ginrunner", 400, 100), create_text\
("Play", 400, 200), create_text("How to play", 400, 250), create_text\
("Exit", 400, 300)};

    while (sfRenderWindow_isOpen(w->window)) {
        w->map = destroy_map(w->map);
        change_color(t, a);
        sfRenderWindow_drawSprite(w->window, back->sprite, NULL);
        sfRenderWindow_drawText(w->window, t[0]->text, NULL);
        sfRenderWindow_drawText(w->window, t[1]->text, NULL);
        sfRenderWindow_drawText(w->window, t[2]->text, NULL);
        sfRenderWindow_drawText(w->window, t[3]->text, NULL);
        sfRenderWindow_display(w->window);
        sfRenderWindow_clear(w->window, sfWhite);
        a = menu_event(w, a, back);
    }
    destroy_everything(w);
}

int main(void)
{
    menu();
}
