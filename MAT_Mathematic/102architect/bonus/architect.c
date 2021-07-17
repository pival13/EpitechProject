/*
** EPITECH PROJECT, 2018
** architect.c
** File description:
** draw a window for architect
*/

#include <SFML/Graphics.h>
#include "csfml.h"

int main(int n, char **arg)
{
    window_t *window = create_struct_window(SCREEN_X, SCREEN_Y, "Architect");

    put_pixel(window->fb, SCREEN_X/2, SCREEN_Y/2, sfGreen);
    while (sfRenderWindow_isOpen(window->window)) {
        display_window(window);
        while (sfRenderWindow_pollEvent(window->window, &(window->event))) {
            (window->event.type == sfEvtClosed) ? (sfRenderWindow_close(window->window)) : (window->window);
        }
    }
    destroy_everything(window);
}
