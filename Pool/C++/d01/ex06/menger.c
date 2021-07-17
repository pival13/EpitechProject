/*
** EPITECH PROJECT, 2020
** menger
** File description:
** the menger sponge
*/

#include "menger.h"
#include "drawing.h"
#include "bitmap.h"
#include <fcntl.h>

void menger_face(char *filename, size_t size, int recur)
{
    unsigned int *buffer = malloc(size * size * sizeof(*buffer));
    unsigned int **img = malloc(size * sizeof(*img));
    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY , 0644);

    if (buffer == NULL || img == NULL || fd == -1)
        exit(84);
    memset(buffer, 0, size*size*sizeof(*buffer));
    for (size_t i = 0; i < size; i++)
        img[i] = buffer + i * size;
    menger(size, (int[2]){0, recur}, (int[2]){0, 0}, img);
    draw_file(fd, size, buffer);
    close(fd);
}

void menger(int len, int recur[2], int p[2], unsigned int **img)
{
    int new_recur[2] = {recur[0]+1, recur[1]};
    unsigned int color;

    if (recur[0] < recur[1]) {
        color = 0xFF / (recur[1]-recur[0]);
        color = (color << 16) + (color << 8) + color;
        draw_square(img, (int[2]){p[0]+len/3, p[1]+len/3}, len/3, color);
        menger(len/3, new_recur, (int[2]){p[0], p[1]}, img);
        menger(len/3, new_recur, (int[2]){p[0], p[1]+len/3}, img);
        menger(len/3, new_recur, (int[2]){p[0], p[1]+len/3*2}, img);
        menger(len/3, new_recur, (int[2]){p[0]+len/3, p[1]}, img);
        menger(len/3, new_recur, (int[2]){p[0]+len/3, p[1]+len/3*2}, img);
        menger(len/3, new_recur, (int[2]){p[0]+len/3*2, p[1]}, img);
        menger(len/3, new_recur, (int[2]){p[0]+len/3*2, p[1]+len/3}, img);
        menger(len/3, new_recur, (int[2]){p[0]+len/3*2, p[1]+len/3*2}, img);
    }
}