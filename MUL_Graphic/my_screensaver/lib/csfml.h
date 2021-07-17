/*
** EPITECH PROJECT, 2018
** csfml.h
** File description:
** header of csfml
*/

#include <SFML/Graphics.h>
#define SCREEN_X 800
#define SCREEN_Y 450
#define COLOR sfColor_fromInteger
#define NB_SS 6
#define NB_ARG "%s: bad arguments: %d given but 1 is required\nretry with -h\n"
#define TYPE_ARG "%s: bad arguments: please enter a number between \
1 and %d\nretry with -h\n"
#define USAGE "Animation rendering in a CSFML window.\n\nUSAGE\n ./my_screen\
saver [OPTIONS]/animation_id\n\n   animation_id\t  ID of the animation to pr\
ocess (between 1 and %d).\n\nOPTIONS\n  -d\t\t\tprint the description of all \
the animations and quit.\n  -h\t\t\tprint the usage and quit.\n\nUSER INTERA\
CTIONS\n  RIGHT_ARROW\t\tswitch to the next animation.\n  LEFT_ARROW\t\tswit\
ch to the previous animation.\n  LEFT_MOUSE_BUTTON\tAdd new shapes (4 extra \
shapes).\n  RIGHT_MOUSE_BUTTON\tdecrease the number of shapes or stop them.\n\n"
#define DESCRIPTION "1: Draw multicolors lines (between 1 and 5 lines)\n2: \
Draw waves of circles with variant color (between 1 and 5 waves)\n3: Draw \
circles and squares at random position with random size (draw more with \
different color when clicking)\n4: Draw some line from the center to the \
border of the screen (draw with different color when clicking)\n5: Draw \
fireworks (draw with different color when clicking)\n6: Draw color circle \
in the previous circle (between 1 and 5 circle)\n"
#define W window
#define PT_X x-center.x
#define PT_Y y-center.y
#define COEFX (a.y-b.y)/(a.x-b.x)
#define COEFY (a.x-b.x)/(a.y-b.y)
#define INIT_POINT {{100, 101}, {SCREEN_X / 2, SCREEN_Y / 2}, {400, 180}, \
{200, 320}, {27, 56}}
#define INIT_COLOR {COLOR(65535), COLOR(4278190335), COLOR(16711935), COLOR\
(255), COLOR(4294967295)}

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
void put_pixel(framebuffer_t *fb, unsigned int x, unsigned int y, sfColor \
color);
int draw_line(framebuffer_t *fb, sfVector2f a, sfVector2f bn, sfColor color);
int draw_circle(framebuffer_t *fb, sfVector2f center, int radius, sfColor \
color);
void draw_bloc(framebuffer_t *fb, sfVector2f origin, unsigned int size, \
sfColor color);
void move_up(framebuffer_t *fb);
void move_down(framebuffer_t *fb);
void move_right(framebuffer_t *fb);
void move_left(framebuffer_t *fb);
void dissolve(framebuffer_t *fb);
void draw_square(framebuffer_t *fb, sfVector2f origin, unsigned int size, \
sfColor color);
sfColor change_color(sfColor color);
int ss1(framebuffer_t *, sfVector2f *, int sens[2], sfColor);
int ss2(framebuffer_t *, sfVector2f *, int sens[2], sfColor);
int ss3(framebuffer_t *, sfVector2f *, int sens[2], sfColor);
int ss4(framebuffer_t *, sfVector2f *, int sens[2], sfColor);
int ss5(framebuffer_t *, sfVector2f *, int sens[2], sfColor);
int ss6(framebuffer_t *, sfVector2f *, int sens[2], sfColor);

#endif //CSFMH_H_
