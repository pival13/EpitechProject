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

void draw_square(uint32_t **img, const int origin[2], size_t size, \
uint32_t color);
void draw_file(int fd, int size, unsigned int *buffer);

#endif