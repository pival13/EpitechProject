/*
** EPITECH PROJECT, 2018
** csfml.h
** File description:
** header of csfml
*/

#include <SFML/Graphics.h>

#define SCREEN_X 800
#define SCREEN_Y 450

#ifndef CSFML_H_
#define CSFML_H_

typedef struct framebuffer {
    unsigned int width;
    unsigned int height;
    unsigned char *pixel;
} framebuffer_t;

typedef struct window_s {
    sfVideoMode mode;
    sfRenderWindow *window;
    sfEvent event;
    sfTexture *texture;
    sfSprite *sprite;
    framebuffer_t *fb;
} window_t;

window_t *create_struct_window(int, int, char *);
framebuffer_t *framebuffer_create(unsigned int width, unsigned int height);
void put_pixel(framebuffer_t *framebuffer, unsigned int x, unsigned int y, sfColor color);
int draw_line(framebuffer_t *fb, sfVector2f a, sfVector2f bn, sfColor color);
int draw_circle(framebuffer_t *fb, sfVector2f center, int radius, sfColor color);
sfColor change_color(sfColor color);
int destroy_everything(window_t *w);
int display_window(window_t *window);
int screensaver1(framebuffer_t *fb, sfVector2f *ball, int sens[2], sfColor color);

#endif //CSFMH_H_
