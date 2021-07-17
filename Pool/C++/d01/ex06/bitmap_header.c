/*
** EPITECH PROJECT, 2020
** bitmap_header.c
** File description:
** header generator for BMP file
*/

#include "bitmap.h"

void make_bmp_header(bmp_header_t *header, size_t size)
{
    if (header == NULL)
        return;
    header->magic = 0x4D42;
    header->size = size * size * 32 / 8 + sizeof(bmp_header_t) + \
sizeof(bmp_info_header_t);
    header->_app1 = 0;
    header->_app2 = 0;
    header->offset = sizeof(bmp_header_t) + sizeof(bmp_info_header_t);
}

void make_bmp_info_header(bmp_info_header_t *header, size_t size)
{
    if (header == NULL)
        return;
    header->size = sizeof(bmp_info_header_t);
    header->width = size;
    header->height = size;
    header->planes = 1;
    header->bpp = 32;
    header->compression = 0;
    header->raw_data_size = size * size * 32 / 8;
    header->h_resolution = 0;
    header->v_resolution = 0;
    header->palette_size = 0;
    header->important_colors = 0;
}