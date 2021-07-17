/*
** EPITECH PROJECT, 2019
** menu
** File description:
** menu page
*/

#include <stdlib.h>
#include "csfml.h"

int event_level(window_t *w, int *a)
{
    if (sfRenderWindow_pollEvent(w->window, &w->event)) {
        if (w->event.type == sfEvtClosed)
            sfRenderWindow_close(w->window);
        if (w->event.type == sfEvtKeyPressed && w->event.key.code == sfKeyUp)
            *a = (*a+2) % 3;
        if (w->event.type == sfEvtKeyPressed && w->event.key.code == sfKeyDown)
            *a = (*a+1) % 3;
        if (w->event.type == sfEvtKeyPressed && w->event.key.code == sfKey\
Return) {
            if (*a == 0)
                game(w, "bonus/map2");
            else if (*a == 1)
                game(w, "bonus/map1");
            return (1);
        }
    }
    return (0);
}

void choose_level(window_t *w, object_t *back)
{
    text_t *t[4] = {create_text("Chose your level", 400, 100), create_text\
("Map test", 400, 200), create_text("Map 1", 400, 250), create_text("Back"\
, 400, 300)};
    int a = 0;

    while (sfRenderWindow_isOpen(w->window)) {
        change_color(t, a);
        sfRenderWindow_drawSprite(w->window, back->sprite, NULL);
        sfRenderWindow_drawText(w->window, t[0]->text, NULL);
        sfRenderWindow_drawText(w->window, t[1]->text, NULL);
        sfRenderWindow_drawText(w->window, t[2]->text, NULL);
        sfRenderWindow_drawText(w->window, t[3]->text, NULL);
        sfRenderWindow_display(w->window);
        sfRenderWindow_clear(w->window, sfWhite);
        if (event_level(w, &a) == 1)
            return;
    }
}

void how_to_play(window_t *w, object_t *back)
{
    text_t *t[6] = {TEXT("How to play", 400, 90), TEXT("* Press Space to jump"\
, 400, 140), TEXT("* Press Escape to stop the level", 400, 190), TEXT("* If you\
 hit a wall, walked on spike", 400, 240), TEXT(" or fall in hole, you lose", 40\
0, 280), TEXT("Back", 400, 330)};

    sfText_setColor(t[5]->text, sfCyan);
    while (sfRenderWindow_isOpen(w->window)) {
        sfRenderWindow_drawSprite(w->window, back->sprite, NULL);
        for (int i = 0; i != 6; i++)
            sfRenderWindow_drawText(w->window, t[i]->text, NULL);
        sfRenderWindow_display(w->window);
        sfRenderWindow_clear(w->window, sfWhite);
        if (sfRenderWindow_pollEvent(w->window, &w->event)) {
            if (w->event.type == sfEvtClosed)
                sfRenderWindow_close(w->window);
            if (w->event.type == sfEvtKeyPressed && w->event.key.code == sfKey\
Return)
                return;
        }
    }
}
