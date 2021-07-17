/*
** EPITECH PROJECT, 2019
** my_world.h
** File description:
** header of my_world
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <unistd.h>

#ifndef MY_WORLD_H
#define MY_WORLD_H

#define SIZE(a) (float)sfRenderWindow_getSize(w->window).a
#define BSIZE(a) (float)w->mode.a
#define TSIZE(text, a) (float)sfTexture_getSize(text).a
#define COEFF(text) (SIZE(x)/TSIZE(text, x)/BSIZE(height)*TSIZE(text, y \
) > SIZE(y)/BSIZE(height)) ? (sfVector2f){BSIZE(width)/TSIZE(text, x), \
SIZE(x)*BSIZE(height)/TSIZE(text, x)/SIZE(y)} : (sfVector2f){SIZE(y)*BS\
IZE(width)/SIZE(x)/TSIZE(text, y), BSIZE(height)/TSIZE(text, y)}
#define KEY(letter) (w->event.type == sfEvtKeyPressed && w->event.key.co\
de == letter)
#define TEXT(letter) (w->event.type == sfEvtTextEntered && w->event.tex\
t.unicode == letter)
#define SCROLL(sign) (w->event.type == sfEvtMouseWheelScrolled && w->eve\
nt.mouseWheelScroll.delta sign 0)

typedef struct cell_s {
    sfConvexShape *shape;
    sfVector2f pos;
    int height;
} cell_t;

typedef struct page_s {
    sfText **text;
    sfTexture *tbackground;
    sfTexture *tbutton[7];
    sfRectangleShape *rbutton[14];
    sfSprite *background;
} page_t;

typedef struct world_s {
    sfCircleShape *circle;
    sfVideoMode mode;
    sfRenderWindow *window;
    sfMusic *music[2];
    sfEvent event;
    page_t *page;
    sfTexture *texture[7];
    cell_t **map;
    sfFont *font;
} world_t;

void destroy(world_t *w);
void condition(world_t *w, int i);
world_t *create_map(char *);
void load_map(world_t *w, char **world);
void create_texture(world_t *w);
sfText *create_text(char *str, int size, sfFont *font);
void create_page(world_t *w);
void move_text(sfText *t, int x, int y);
void color_text(sfText *t, sfColor color);
void edit_map_height(world_t *w, int x, int y, int height);
void edit_map_texture(world_t *w, int x, int y, int nb_text);
int passed_text(world_t *w, sfText *text);
int passed_button(world_t *w, sfRectangleShape *button);
int passed_shape(sfVector2f mouse, sfConvexShape *shape, world_t *w);
void change_map(world_t *w, int type);
int cmp_color(sfColor c1, sfColor c2);
void edit_map(world_t *w, float change_angle[2], float change_pos[2]\
, float change_size);
void move_map(world_t *w, int *type);

#endif
