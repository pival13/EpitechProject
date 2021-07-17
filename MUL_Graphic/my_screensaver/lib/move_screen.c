/*
** EPITECH PROJECT, 2018
** move_screen
** File description:
** move each pixel of the screen
*/

#include "csfml.h"
#include <SFML/Graphics.h>

void move_left(framebuffer_t *fb)
{
    for (int i = 0; i != SCREEN_X-1; i++)
        for (int j = 0; j != SCREEN_Y-1; j++) {
            fb->pixel[(fb->width * j + i) * 4] = fb->pixel[(fb->width * j \
+ i + 1) * 4];
            fb->pixel[(fb->width * j + i) * 4 + 1] = fb->pixel[(fb->width \
* j + i + 1) * 4 + 1];
            fb->pixel[(fb->width * j + i) * 4 + 2] = fb->pixel[(fb->width \
* j + i + 1) * 4 + 2];
            fb->pixel[(fb->width * j + i) * 4 + 3] = fb->pixel[(fb->width \
* j + i + 1) * 4 + 3];
        }
    for (int j = 0; j != SCREEN_Y-1; j++) {
        fb->pixel[(fb->width * j + SCREEN_X-1) * 4] = 0;
        fb->pixel[(fb->width * j + SCREEN_X-1) * 4 + 1] = 0;
        fb->pixel[(fb->width * j + SCREEN_X-1) * 4 + 2] = 0;
        fb->pixel[(fb->width * j + SCREEN_X-1) * 4 + 3] = 255;
    }
}

void move_right(framebuffer_t *fb)
{
    for (int i = SCREEN_X-1; i != 0; i--)
        for (int j = 0; j != SCREEN_Y-1; j++) {
            fb->pixel[(fb->width * j + i) * 4] = fb->pixel[(fb->width * j \
+ i - 1) * 4];
            fb->pixel[(fb->width * j + i) * 4 + 1] = fb->pixel[(fb->width \
* j + i - 1) * 4 + 1];
            fb->pixel[(fb->width * j + i) * 4 + 2] = fb->pixel[(fb->width \
* j + i - 1) * 4 + 2];
            fb->pixel[(fb->width * j + i) * 4 + 3] = fb->pixel[(fb->width \
* j + i - 1) * 4 + 3];
        }
    for (int j = 0; j != SCREEN_Y-1; j++) {
        fb->pixel[(fb->width * j) * 4] = 0;
        fb->pixel[(fb->width * j) * 4 + 1] = 0;
        fb->pixel[(fb->width * j) * 4 + 2] = 0;
        fb->pixel[(fb->width * j) * 4 + 3] = 255;
    }
}

void move_up(framebuffer_t *fb)
{
    for (int i = 0; i != SCREEN_X; i++) {
        for (int j = 0; j != SCREEN_Y-1; j++) {
            fb->pixel[(fb->width * j + i) * 4] = fb->pixel[(fb->width * (j \
+ 1) + i) * 4];
            fb->pixel[(fb->width * j + i) * 4 + 1] = fb->pixel[(fb->width \
* (j + 1) + i) * 4 + 1];
            fb->pixel[(fb->width * j + i) * 4 + 2] = fb->pixel[(fb->width \
* (j + 1) + i) * 4 + 2];
            fb->pixel[(fb->width * j + i) * 4 + 3] = fb->pixel[(fb->width \
* (j + 1) + i) * 4 + 3];
        }
    }
    for (int i = 0; i != SCREEN_X; i++) {
        fb->pixel[(fb->width * (SCREEN_Y-1) + i) * 4] = 0;
        fb->pixel[(fb->width * (SCREEN_Y-1) + i) * 4 + 1] = 0;
        fb->pixel[(fb->width * (SCREEN_Y-1) + i) * 4 + 2] = 0;
        fb->pixel[(fb->width * (SCREEN_Y-1) + i) * 4 + 3] = 255;
    }
}

void move_down(framebuffer_t *fb)
{
    for (int i = 0; i != SCREEN_X; i++) {
        for (int j = SCREEN_Y-1; j != 0; j--) {
            fb->pixel[(fb->width * j + i) * 4] = fb->pixel[(fb->width * (j \
- 1) + i) * 4];
            fb->pixel[(fb->width * j + i) * 4 + 1] = fb->pixel[(fb->width \
* (j - 1) + i) * 4 + 1];
            fb->pixel[(fb->width * j + i) * 4 + 2] = fb->pixel[(fb->width \
* (j - 1) + i) * 4 + 2];
            fb->pixel[(fb->width * j + i) * 4 + 3] = fb->pixel[(fb->width \
* (j - 1) + i) * 4 + 3];
        }
    }
    for (int i = 0; i != SCREEN_X; i++) {
        fb->pixel[i * 4] = 0;
        fb->pixel[i * 4 + 1] = 0;
        fb->pixel[i * 4 + 2] = 0;
        fb->pixel[i * 4 + 3] = 255;
    }
}
