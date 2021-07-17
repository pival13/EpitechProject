/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** main loop of tetris
*/

#include "tetris.h"

void add_piece(tetris_t *w, int *c)
{
    int nb = 0;

    for (; w->piece[nb].name != NULL; nb++);
    w->ncurr = clock() % nb;
    while (w->piece[w->ncurr].color == 0 || w->piece[w->ncurr].size[0] == 0
    || w->piece[w->ncurr].size[1] == 0)
        w->ncurr = clock() % nb;
    for (int i = 0; w->piece[w->curr].piece[i] != NULL; i++)
        for (int j = 0; w->piece[w->curr].piece[i][j] != '\0'; j++) {
            if (w->piece[w->curr].piece[i][j] == '*' && w->map[i][j] == '0')
                w->map[i][j] = w->piece[w->curr].color + '0';
            else if (w->piece[w->curr].piece[i][j] == '*')
                *c = w->exit;
        }
    draw_tetris(w);
}

void erase_line(tetris_t *w, int i)
{
    for (int a = i; a != -1; a--)
        for (int b = 0; b != w->size[1]; b++)
            if (a == 0)
                w->map[a][b] = '0';
            else
                w->map[a][b] = w->map[a-1][b];
    draw_tetris(w);
}

void check_erase_line(tetris_t *w)
{
    int j = 0;
    static int nb = 0;

    for (int i = 0; i != w->size[0]; i++) {
        for (j = 0; j != w->size[1] && w->map[i][j] > 'a'; j++);
        if (j == w->size[1]) {
            erase_line(w, i);
            nb++;
        }
        if (nb == 5) {
            w->speed += 0.3;
            nb = 0;
        }
    }
}

void fix_piece(tetris_t *w, int *c)
{
    for (int i = w->size[0] - 1; i != -1; i--)
        for (int j = 0; j != w->size[1]; j++)
            if (w->map[i][j] > '0' && w->map[i][j] <= '9')
                w->map[i][j] += 'a' - '0';
    w->curr = w->ncurr;
    check_erase_line(w);
    add_piece(w, c);
    draw_tetris(w);
}

void decrease_piece(tetris_t *w, int *c)
{
    if (!can_move(w, 2))
        return (fix_piece(w, c));
    for (int i = w->size[0] - 1; i != 0; i--)
        for (int j = 0; j != w->size[1]; j++)
            if (w->map[i-1][j] > '0' && w->map[i-1][j] <= '9') {
                w->map[i][j] = w->map[i-1][j];
                w->map[i-1][j] = '0';
            }
    check_erase_line(w);
    draw_tetris(w);
}
