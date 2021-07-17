/*
** EPITECH PROJECT, 2018
** csfml.h
** File description:
** header of csfml
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>

#define SCREEN_X 800
#define SCREEN_Y 450
#define PT_X x-center.x
#define PT_Y y-center.y
#define COEFX (a.y-b.y)/(a.x-b.x)
#define COEFY (a.x-b.x)/(a.y-b.y)

#ifndef CSFML_H_
#define CSFML_H_

typedef struct rect_s {
    sfRectangleShape *rect;
    sfVector2f size;
    sfVector2f pos;
    sfColor color;
} rect_t;

typedef struct window_s {
    sfVideoMode mode;
    sfRenderWindow *window;
    sfEvent event;
    sfTexture *texture;
    sfSprite *sprite;
} window_t;

window_t *create_struct_window(int width, int height, char *name, char *\
filepath);
sfColor change_color(sfColor color);
int destroy_everything(window_t *w);
int display_window(window_t *w);

#endif //CSFMH_H_
