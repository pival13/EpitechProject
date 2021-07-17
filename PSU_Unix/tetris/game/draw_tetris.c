/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** main loop of tetris
*/

#include "tetris.h"
#include <string.h>

void draw(char *str, int i, int j, int color)
{
    if (color)
        attron(COLOR_PAIR(color));
    mvprintw(i, j, str);
    if (color)
        attroff(COLOR_PAIR(color)); 
}

void draw_tetris(tetris_t *w)
{
    clear();
    for (int j = 0; j != 2*w->size[1]+4; j++) {
        draw("-", 0, j, 0);
        draw("-", w->size[0]+1, j, 0);
    }
    for (int i = 0; i != w->size[0]; i++) {
        draw("|", i+1, 0, 0);
        draw("|", i+1, 2*w->size[1]+3, 0);
        for (int j = 0; j != w->size[1]; j++)
            if (w->map[i][j] > '0' && w->map[i][j] <= '9')
                draw("**", i+1, 2*j+2, w->map[i][j] - '0');
            else if (w->map[i][j] > 'a')
                draw("**", i+1, 2*j+2, w->map[i][j] - 'a');
    }
    for (int i = 0; i != w->piece[w->ncurr].size[1]; i++)
        for (int j = 0; j != w->piece[w->ncurr].size[0]; j++)
            if (w->piece[w->ncurr].piece[i][j] == '*')
                draw("**", i+1, 2*(j+w->size[1]+3), w->piece[w->ncurr].color);
    refresh();
}
