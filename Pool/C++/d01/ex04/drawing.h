/*
** EPITECH PROJECT, 2020
** drawing.h
** File description:
** header of drawing
*/

#ifndef DRAWING_H
#define DRAWING_H

#include <stdint.h>
#include <stdlib.h>

typedef struct point_s {
    uint32_t x;
    uint32_t y;
} point_t;

void draw_square(uint32_t **img, const point_t *origin, size_t size, \
uint32_t color);

#endif