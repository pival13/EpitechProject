/*
** EPITECH PROJECT, 2020
** drawing.c
** File description:
** draw a square
*/

#include "drawing.h"
#include "bitmap.h"
#include <unistd.h>

void draw_square(uint32_t **img, const int origin[2], size_t size, \
uint32_t color)
{
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            img[origin[1]+i][origin[0]+j] = color;
}

void draw_file(int fd, int size, unsigned int *buffer)
{
    bmp_header_t header;
    bmp_info_header_t info;

    make_bmp_header(&header, size);
    write(fd, &header, sizeof(header));
    make_bmp_info_header(&info, size);
    write(fd, &info, sizeof(info));
    write(fd, buffer, size*size*sizeof(*buffer));
    close(fd);
}