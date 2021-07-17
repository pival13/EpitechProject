/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** main loop of tetris
*/

#include "my.h"

void init_window(void)
{
    if (!(initscr()))
        my_putstr_error("Cannot init term.\n");
    start_color();
    init_pair(1, 1, 1);
    init_pair(2, 2, 2);
    init_pair(3, 3, 3);
    init_pair(4, 4, 4);
    init_pair(5, 5, 5);
    init_pair(6, 6, 6);
    init_pair(7, 7, 7);
    curs_set(false);
    keypad(stdscr, true);
    nodelay(stdscr, true);
    noecho();
    srand(getpid());
}

void init_tetris(tetris_t *w)
{
    int nb = 0;

    w->map = malloc(sizeof(char *) * (w->size[0]));
    for (int i = 0; i != w->size[0]; i++) {
        w->map[i] = malloc(sizeof(char) * (w->size[1]));
        for (int j = 0; j != w->size[1]; j++)
            w->map[i][j] = '0';
    }
    for (; w->piece[nb].name != NULL; nb++);
    w->curr = rand() % nb;
    while (w->piece[w->curr].color == 0 || w->piece[w->curr].size[0] == 0 |\
| w->piece[w->curr].size[1] == 0)
        w->curr = rand() % nb;
    w->speed = 0.7 + w->lvl * 0.3;
    init_window();
    add_piece(w, &nb);
}

void pause_game(tetris_t *w, clock_t *timer, int c)
{
    static clock_t save = 0;

    if (save == 0)
        save = clock() - *timer;
    *timer = clock() - save;
    if (c == -w->pause) {
        save = 0;
        w->pause *= -1;
    }
}

void tetris(tetris_t *w)
{
    int c = ERR;
    clock_t timer = clock();

    init_tetris(w);
    while (c != w->exit) {
        c = getch();
        if (w->pause > 0) {
            if (c != ERR)
                move_piece(w, c);
            if (clock() - 1000000/w->speed > timer || c == w->down) {
                decrease_piece(w, &c);
                timer = clock();
            }
        } else
            pause_game(w, &timer, c);
    }
    endwin();
}
