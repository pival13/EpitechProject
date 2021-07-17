/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** main
*/

#include "csfml.h"
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <time.h>

int clear_fb(framebuffer_t *fb, sfColor color)
{
    for (int i = 1; i <= SCREEN_Y; i++)
        for (int j = 1; j <= SCREEN_X; j++)
            put_pixel(fb, j, i, color);
}

int catch_event(window_t *W, int *nb_clic)
{
    while (sfRenderWindow_pollEvent(W->W, &(W->event))) {
        (W->event.type == sfEvtClosed || (W->event.type == sfEvtKeyPressed \
&& W->event.key.code == sfKeyEscape)) ? (sfRenderWindow_close(W->W)) : (W->W);
        (W->event.type == sfEvtMouseButtonPressed && W->event.mouseButton.\
button == sfMouseLeft && nb_clic[0] < 5) ? (nb_clic[0] += 1) : (nb_clic[0]);
        (W->event.type == sfEvtMouseButtonPressed && W->event.mouseButton.\
button == sfMouseRight && nb_clic[0] > 0) ? (nb_clic[0] -= 1) : (nb_clic[0]);
        (W->event.type == sfEvtKeyPressed && W->event.key.code == sfKeyRight) \
? (clear_fb(W->fb, sfBlack), nb_clic[1] += 1, nb_clic[0] = 1) : (0);
        (W->event.type == sfEvtKeyPressed && W->event.key.code == sfKeyLeft)\
? (clear_fb(W->fb, sfBlack), nb_clic[1] -= 1, nb_clic[0] = 1) : (0);
        (nb_clic[1] < 0) ? (nb_clic[1] += NB_SS) : (nb_clic[1]);
        nb_clic[1] %= NB_SS;
    }
}

int destroy_everything(window_t *W)
{
    free(W->fb->pixel);
    free(W->fb);
    sfTexture_destroy(W->texture);
    sfSprite_destroy(W->sprite);
    sfRenderWindow_destroy(W->W);
    free(W);
}

int display_window(framebuffer_t *fb, sfTexture *texture, sfSprite *sprite, \
sfRenderWindow *W)
{
    sfColor color = COLOR(1);

    sfRenderWindow_setFramerateLimit(W, 100);
    sfSprite_setTexture(sprite, texture, sfFalse);
    sfTexture_updateFromPixels(texture, fb->pixel, SCREEN_X, SCREEN_Y, 0, 0);
    sfRenderWindow_clear(W, color);
    sfRenderWindow_drawSprite(W, sprite, NULL);
    sfRenderWindow_display(W);
}

int main2(int a)
{
    window_t *W = create_struct_window(SCREEN_X, SCREEN_Y, "my_screensaver");
    sfVector2f point[5] = INIT_POINT;
    sfColor color[5] = INIT_COLOR;
    int (*ss[NB_SS])(framebuffer_t *, sfVector2f *, int [2], sfColor) = {ss1, \
ss2, ss3, ss4, ss5, ss6};
    int sens[10] = {-1, -1, -1, 1, 1, 1, 1, -1, 1, -1};
    int nb_clic[2] = {1, a-1};

    srand(time(0));
    while (sfRenderWindow_isOpen(W->W)) {
        for (int i = 0; i != nb_clic[0] && i != 5; i++)
            (*ss[nb_clic[1]])(W->fb, &point[i], &sens[2*i], color[i] \
= change_color(color[i]));
        display_window(W->fb, W->texture, W->sprite, W->W);
        catch_event(W, nb_clic);
    }
    destroy_everything(W);
}
