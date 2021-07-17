/*
** EPITECH PROJECT, 2019
** character_menu2.c
** File description:
** character_menu2
*/

#include "my.h"

void character_menu_interactions(rpg_t *w, int *a, int *b)
{
    if ((click_button(w->cursor, w->ch->button_right, w->event) == 1 ||
        KEY_D()) && *a < 4) {
        *a += 1;
        *b += 2;
    }
    if ((click_button(w->cursor, w->ch->button_left, w->event) == 1 ||
        KEY_Q()) && *a >= 1) {
        *a -= 1;
        *b -= 2;
    }
}

void character_menu_set_sprite(rpg_t *w, int *a, int *b, sfSprite *str[11])
{
    if (w->player[*a].sexe == 1) {
        sfSprite_setScale(str[*b], (sfVector2f){SIZE(y) / 2 /
        (float)sfSprite_getLocalBounds(str[*b]).height, SIZE(y) / 2
        / (float)sfSprite_getLocalBounds(str[*b]).height});
        sfRenderWindow_drawSprite(w->win, str[*b], NULL);
    }
    else {
        sfSprite_setScale(str[*b + 1], (sfVector2f){SIZE(y) / 2
        / (float)sfSprite_getLocalBounds(str[*b]).height, SIZE(y) / 2
        / (float)sfSprite_getLocalBounds(str[*b + 1]).height});
        sfRenderWindow_drawSprite(w->win, str[*b + 1], NULL);
    }
}
