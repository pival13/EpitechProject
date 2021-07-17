/*
** EPITECH PROJECT, 2019
** solver
** File description:
** solver of solver
*/

#include "dante.h"

int nb_way(solver_t *w, int x, int y)
{
    int nb = 0;
    int len = strlen(w->map)-1;

    if (x*w->len+y == (int)strlen(w->map) - 1)
        return (0);
    if ((x+1)*w->len+y <= len && w->map[(x+1)*w->len+y] == '*')
        nb++;
    if (x > 0 && w->map[(x-1)*w->len+y] == '*')
        nb++;
    if (y+1 < w->len && w->map[x*w->len+y+1] == '*')
        nb++;
    if (y > 0 && w->map[x*w->len+y-1] == '*')
        nb++;
    return (nb);
}

void new_move(solver_t *w, int *x, int *y)
{
    int len = strlen(w->map)-1;

    if ((*x+1)*w->len+*y <= len && w->map[(*x+1)*w->len+*y] == '*')
        *x += 1;
    if (*x > 0 && w->map[(*x-1)*w->len+*y] == '*')
        *x -= 1;
    if (*y+1 < w->len && w->map[*x*w->len+*y+1] == '*')
        *y += 1;
    if (*y > 0 && w->map[*x*w->len+*y-1] == '*')
        *y -= 1;
}

int solved_semi_recur(solver_t *w, int x, int y)
{
    int len = strlen(w->map);

    if (x < 0 || y >= w->len-1 || y < 0 || x*w->len+y > len || \
w->map[x*w->len+y] != '*')
        return (0);
    while (nb_way(w, x, y) == 1) {
        w->map[x*w->len+y] = 'o';
        new_move(w, &x, &y);
    }
    w->map[x*w->len+y] = 'o';
    if (x*w->len+y == len-1 || solved_semi_recur(w, x+1, y) || \
solved_semi_recur(w, x, y+1) || solved_semi_recur(w, x-1, y) || \
solved_semi_recur(w, x, y-1))
        return (1);
    return (0);
}