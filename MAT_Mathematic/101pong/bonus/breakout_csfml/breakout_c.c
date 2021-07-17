/*
** EPITECH PROJECT, 2018
** breakout_c
** File description:
** A breakout game in C
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"

#define SIZE_X 192
#define SIZE_Y 50

typedef struct framebuffer {
    unsigned int width;
    unsigned int height;
    unsigned char *pixel;
} framebuffer_t;

int game(int n, char **arg, int nb, int *brique, int pos_brique[nb][2]);

framebuffer_t *framebuffer_create(unsigned int width, unsigned int height)
{
    framebuffer_t *framebuffer;

    framebuffer = malloc(sizeof(framebuffer_t));
    framebuffer->width = width;
    framebuffer->height = height;
    framebuffer->pixel = malloc(width * height * 4);
    return (framebuffer);
}

void put_pixel(framebuffer_t *framebuffer, unsigned int x, unsigned int y, sfColor color)
{
    int red = color.r;
    int green = color.g;
    int blue = color.b;
    int alpha = color.a;

    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4] = red;
    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4 + 1] = green;
    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4 + 2] = blue;
    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4 + 3] = alpha;
}

void draw_square(framebuffer_t *framebuffer, int x, int y, unsigned int width, unsigned int height, sfColor color, sfColor color2)
{
    if (width == 1 && height == 1) {
        put_pixel(framebuffer, x, y, color);
        return;
    } else {
        for (int i = 0; i != width; i++)
            put_pixel(framebuffer, x, y + i, color);
        for (int i = 0; i != height; i++) {
            put_pixel(framebuffer, x + 1 + i, y, color);
            for (int j = 1; j != width - 1; j++)
                put_pixel(framebuffer, x + 1 + i, y + j, color2);
            put_pixel(framebuffer, x + 1 + i, y + width - 1, color);
        }
        for (int i = 0; i != width; i++)
            put_pixel(framebuffer, x + height, y + i, color);
        return;
    }
}

sfCircleShape *draw_circle(int radius)
{
    sfVector2f origin_ball = {radius, radius};
    sfCircleShape *circle = sfCircleShape_create();

    sfCircleShape_setRadius(circle, radius);
    sfCircleShape_setOutlineColor(circle, sfBlack);
    sfCircleShape_setFillColor(circle, sfYellow);
    sfCircleShape_setOutlineThickness(circle, 1);
    sfCircleShape_setOrigin(circle, origin_ball);
    return (circle);
}

sfTexture *make_brique(int nb, int pos_brique[nb][2])
{
    framebuffer_t *fb2 = framebuffer_create(SIZE_X + 1, SIZE_Y + 1);
    sfTexture *brique = sfTexture_create(1915, 251);
    
    draw_square(fb2, 1, 1, SIZE_Y, SIZE_X, sfBlack, sfRed);
    for (int i = 0; i != nb; i++)
        sfTexture_updateFromPixels(brique, fb2->pixel, SIZE_X + 1, SIZE_Y + 1, pos_brique[i][0], pos_brique[i][1]);
    return (brique);
}

sfColor change_color(sfColor color, int c_color)
{
    (color.r == 255 && color.g < 255 && color.b == 0 && c_color == 1) ? color.g++ : color.g;
    (color.r > 0 && color.g == 255 && color.b == 0 && c_color == 1) ? color.r-- : color.r;
    (color.r == 0 && color.g == 255 && color.b < 255 && c_color == 1) ? color.b++ : color.b;
    (color.r == 0 && color.g > 0 && color.b == 255 && c_color == 1) ? color.g-- : color.g;
    (color.r < 255 && color.g == 0 && color.b == 255 && c_color == 1) ? color.r++ : color.r;
    (color.r == 255 && color.g == 0 && color.b > 0 && c_color == 1) ? color.b-- : color.b;
    return (color);
}

void touch_brique(sfVector2f move, sfTexture *texture, int *brique, int *sens, int n_brique, int nb, int pos_brique[nb][2])
{
    framebuffer_t *fb = framebuffer_create(SIZE_X + 1, SIZE_Y + 1);

    if (brique[n_brique] == 0) {
        draw_square(fb, 1, 1, SIZE_Y, SIZE_X, sfTransparent, sfTransparent);
        (move.y < 14 + SIZE_Y + pos_brique[n_brique][1] && move.y > 14 + SIZE_Y + pos_brique[n_brique][1] - 5 && move.x > pos_brique[n_brique][0] - 14 && move.x < pos_brique[n_brique][0] + 14 + SIZE_X && brique[n_brique] == 0) ? (sfTexture_updateFromPixels(texture, fb->pixel, SIZE_X + 1, SIZE_Y + 1, pos_brique[n_brique][0], pos_brique[n_brique][1]), brique[n_brique] = 1, sens[1] = -1) : sens[1];
        (move.y < pos_brique[n_brique][1] + 5 - 14 && move.y > pos_brique[n_brique][1] - 14 && move.x > pos_brique[n_brique][0] - 14 && move.x < pos_brique[n_brique][0] + SIZE_X + 14 && brique[n_brique] == 0) ? (sfTexture_updateFromPixels(texture, fb->pixel, SIZE_X + 1, SIZE_Y + 1, pos_brique[n_brique][0], pos_brique[n_brique][1]), brique[n_brique] = 1, sens[1] = 1) : sens[1];
        (move.y < SIZE_Y + pos_brique[n_brique][1] + 14 && move.y > pos_brique[n_brique][1] - 14 && move.x > pos_brique[n_brique][0] - 14 && move.x < pos_brique[n_brique][0] + 5 - 14 && brique[n_brique] == 0) ? (sfTexture_updateFromPixels(texture, fb->pixel, SIZE_X + 1, SIZE_Y + 1, pos_brique[n_brique][0], pos_brique[n_brique][1]), brique[n_brique] = 1, sens[0] = 1) : sens[0];
        (move.y < SIZE_Y + pos_brique[n_brique][1] + 14 && move.y > pos_brique[n_brique][1] - 14 && move.x > pos_brique[n_brique][0] + SIZE_X + 14 - 5 && move.x < pos_brique[n_brique][0] + SIZE_X + 14 && brique[n_brique] == 0) ? (sfTexture_updateFromPixels(texture, fb->pixel, SIZE_X + 1, SIZE_Y + 1, pos_brique[n_brique][0], pos_brique[n_brique][1]), brique[n_brique] = 1, sens[0] = -1) : sens[0];
    }
    free(fb->pixel);
    free(fb);
}

int new_game(int n, char **arg, int nb)
{
    if (nb == 10) {
        nb = 15;
        int brique[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int pos_brique[15][2] = {{0, 0}, {384, 0}, {768, 0}, {1152, 0}, {1531, 0}, {192, 50}, {576, 50}, {960, 50}, {1342, 50}, {1720, 50}, {0, 100}, {384, 100}, {768, 100}, {1152, 100}, {1531, 100}};
        game(n, arg, nb, brique, pos_brique);
    } else if (nb == 15) {
        nb = 30;
        int brique[30] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int pos_brique[30][2] = {{0, 0}, {384, 0}, {768, 0}, {1152, 0}, {1531, 0}, {192, 50}, {576, 50}, {960, 50}, {1342, 50}, {1720, 50}, {0, 100}, {384, 100}, {768, 100}, {1152, 100}, {1531, 100}, {0, 50}, {384, 50}, {768, 50}, {1152, 50}, {1531, 50}, {192, 100}, {576, 100}, {960, 100}, {1342, 100}, {1720, 100}, {192, 0}, {576, 0}, {960, 0}, {1342, 0}, {1720, 0}};
        game(n, arg, nb, brique, pos_brique);
    }
}

int game(int n, char **arg, int nb, int *brique, int pos_brique[nb][2])
{
    sfVideoMode mode = {1915, 967, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Breakout", sfDefaultStyle, NULL);
    sfEvent event;
    framebuffer_t *fb = framebuffer_create(171, 31);
    framebuffer_t *fb2 = framebuffer_create(SIZE_X + 1, SIZE_Y + 1);
    sfCircleShape *circle = draw_circle(15);
    sfCircleShape *circle2 = sfCircleShape_create();
    sfTexture *wall = sfTexture_createFromFile("bonus/breakout_csfml/brique.jpg", NULL);
    sfSprite *background = sfSprite_create();
    sfSprite *wall_brique = sfSprite_create();
    sfTexture *t_bat = sfTexture_create(171, 31);
    sfSprite *bat = sfSprite_create();
    sfVector2f move = {200, 921};
    sfVector2f origin_ball2 = {10, 0};
    sfVector2f origin_bat = {83, 0};
    sfVector2f scale = {2.82, 2.82};
    sfVector2f position = {950, 937};
    int sens[2] = {-1, 1};
    int begin = 0;
    int c_color = -1;
    float x = 0.6;
    float y = 0.5;
    float mult = 1.0001;
    int compteur = 0;
    int result = 0;
    sfColor color = {200, 200, 200, 100};
    sfColor color_ball = {255, 255, 0, 255};
    sfTexture *texture = make_brique(nb, pos_brique);
    sfMusic *music;

    if (n != 2) {
        my_putstr("Please enter a difficulty (Easy, Hard, Lunatic)\n");
        return (84);
    }
    sfCircleShape_setRadius(circle2, 4);
    sfCircleShape_setFillColor(circle2, sfWhite);
    sfCircleShape_setOrigin(circle2, origin_ball2);
    sfSprite_setOrigin(bat, origin_bat);
    draw_square(fb, 1, 1, 30, 170, sfBlack, sfBlue);
    sfTexture_updateFromPixels(t_bat, fb->pixel, 171, 31, 0, 0);
    sfSprite_setTexture(bat, t_bat, sfTrue);
    sfSprite_setTexture(background, wall, sfFalse);
    sfSprite_setTexture(wall_brique, texture, sfTrue);
    sfSprite_scale(background, scale);
    draw_square(fb2, 1, 1, SIZE_Y, SIZE_X, sfTransparent, sfTransparent);
    if (my_strcmp(arg[1], "Easy") == 0) {
        mult = 1.00001;
        music = sfMusic_createFromFile("bonus/breakout_csfml/Bgm_map_FE13_10.ogg");
    } else if (my_strcmp(arg[1], "Hard") == 0) {
        mult = 1.0001;
        music = sfMusic_createFromFile("bonus/breakout_csfml/Bgm_map_FE15_06.ogg");
    } else if (my_strcmp(arg[1], "Lunatic") == 0) {
        sfCircleShape_setFillColor(circle, color);
        mult += 0.0002;
        c_color = 0;
        music = sfMusic_createFromFile("bonus/breakout_csfml/Bgm_map_FE15_05.ogg");
    }
    else {
        my_putstr("Please enter a difficulty (Easy, Hard, Lunatic)\n");
        return (84);
    }
    sfMusic_setLoop(music, sfTrue);
    sfMusic_play(music);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, background, NULL);
        color_ball = change_color(color_ball, c_color);
        if (c_color == 1 || c_color == -1)
            sfCircleShape_setFillColor(circle, color_ball);
        sfCircleShape_setPosition(circle, move);
        sfCircleShape_setPosition(circle2, move);
        sfSprite_setPosition(bat, position);
        sfSprite_setTexture(wall_brique, texture, sfFalse);
        sfRenderWindow_drawSprite(window, bat, NULL);
        sfRenderWindow_drawSprite(window, wall_brique, NULL);
        sfRenderWindow_drawCircleShape(window, circle, NULL);
        sfRenderWindow_drawCircleShape(window, circle2, NULL);
        sfRenderWindow_display(window);
        if (begin == 0) {
            sens[1] = 1;
            move.y = 921;
        }
        if (begin == 1) {
            (sens[0] == -1) ? (move.x += x) : (move.x -= x);
            (sens[1] == -1) ? (move.y += y) : (move.y -= y);
            (move.y > 967 - 14 - 30 && position.x > move.x - 85 && position.x < move.x + 85) ? (sens[1] = 1) : sens[1];
            (move.y > 967 - 14) ? (begin = 0, compteur++) : move.x;
            for (int i = 0; i != nb; i++)
                touch_brique(move, texture, brique, sens, i, nb, pos_brique);
            (move.y < 14) ? (sens[1] = -1) : sens[1];
            (move.x < 14) ? (sens[0] = -1) : sens[0];
            (move.x > 1915 - 14) ? (sens[0] = 1) : sens[0];     
            x *= mult;
            y *= mult;
        } else {
            move.x = position.x;
            x = 0.6;
            y = 0.5;
        }
        if (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.type == sfEvtKeyPressed)
                if (event.key.code == sfKeyRight)
                    position.x += 25;
                else if (event.key.code == sfKeyLeft)
                    position.x -= 25;
                else if (event.key.code == sfKeyEscape)
                    sfSprite_setColor(bat, sfTransparent);
                else if (event.key.code == sfKeyC)
                    c_color *= -1;
            if (event.type == sfEvtMouseMoved)
                if (event.mouseMove.x > 1825)
                    position.x = 1825;
                else if (event.mouseMove.x < 85)
                    position.x = 85;
                else
                    position.x = event.mouseMove.x;
            if (event.type == sfEvtMouseButtonPressed)
                begin = 1;
        }
        result = 0;
        for (int i = 0; i != nb; i++)
            result += brique[i];
        if (result == nb) {
            sfRenderWindow_close(window);
            new_game(n, arg, nb);
        }
    }
    free(fb->pixel);
    free(fb);
    sfCircleShape_destroy(circle);
    sfTexture_destroy(t_bat);
    sfSprite_destroy(bat);
    sfSprite_destroy(wall_brique);
    sfRenderWindow_destroy(window);
    sfMusic_destroy(music);
    printf("You are dead %d times\n", compteur);
    return (0);
}

int main(int n, char **arg)
{
    int brique[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int pos_brique[10][2] = {{0, 0}, {192, 0}, {384, 0}, {576, 0}, {768, 0}, {960, 0}, {1152, 0}, {1342, 0}, {1531, 0}, {1720, 0}/*, {1152, 200}, {487, 163}*/};
    
    game(n, arg, 10, brique, pos_brique);
}
