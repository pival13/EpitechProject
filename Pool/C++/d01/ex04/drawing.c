/*
** EPITECH PROJECT, 2020
** drawing.c
** File description:
** draw a square
*/

#include "drawing.h"

void draw_square(uint32_t **img, const point_t *origin, size_t size, \
uint32_t color)
{
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            img[origin->y+i][origin->x+j] = color;
}