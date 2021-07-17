/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** main loop of tetris
*/

#include "tetris.h"

int can_move(tetris_t *w, int sens)
{
    for (int i = 0; i != w->size[0]; i++)
        for (int j = 0; j != w->size[1]; j++) {
            if (sens == 1 && w->map[i][j] > '0' && w->map[i][j] <= '9' &\
& (j == w->size[1]-1 || w->map[i][j+1] > 'a'))
                return (0);
            if (sens == 2 && w->map[i][j] > '0' && w->map[i][j] <= '9' &\
& (i == w->size[0]-1 || w->map[i+1][j] > 'a'))
                return (0);
            if (sens == 3 && w->map[i][j] > '0' && w->map[i][j] <= '9' &\
& (j == 0 || w->map[i][j-1] > 'a'))
                return (0);
        }
    return (1);
}

void move_left(tetris_t *w)
{
    for (int i = 0; i != w->size[0]; i++)
        for (int j = 0; j != w->size[1]-1; j++)
            if (w->map[i][j+1] > '0' && w->map[i][j+1] <= '9') {
                w->map[i][j] = w->map[i][j+1];
                w->map[i][j+1] = '0';
            }
}

void move_right(tetris_t *w)
{
    for (int i = 0; i != w->size[0]; i++)
        for (int j = w->size[1]-1; j != 0; j--)
            if (w->map[i][j-1] > '0' && w->map[i][j-1] <= '9') {
                w->map[i][j] = w->map[i][j-1];
                w->map[i][j-1] = '0';
            }
}

void move_piece(tetris_t *w, int c)
{
    if (c == w->left && can_move(w, 3))
        move_left(w);
    if (c == w->right && can_move(w, 1))
        move_right(w);
    if (c == w->rotate)
        rotate_piece(w);
    if (c == w->pause)
        w->pause *= -1;
    draw_tetris(w);
}