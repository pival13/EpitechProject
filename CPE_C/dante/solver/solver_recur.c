/*
** EPITECH PROJECT, 2019
** solver
** File description:
** solver of solver
*/

#include "dante.h"

void clean_map(char *map)
{
    for (int i = 0; map[i] != '\0'; i++)
        if (map[i] == 'u')
            map[i] = '*';
}

int solved_recur(solver_t *w, int x, int y)
{
    int len = strlen(w->map);

    if (x < 0 || y >= w->len-1 || y < 0 || x*w->len+y > len || \
w->map[x*w->len+y] != '*')
        return (0);
    w->map[x*w->len+y] = 'o';
    if (x*w->len+y == len-1)
        clean_map(w->map);
    if (x*w->len+y == len-1 || solved_recur(w, x+1, y) || \
solved_recur(w, x, y+1) || solved_recur(w, x-1, y) || solved_recur(w, x, y-1))
        return (1);
    w->map[x*w->len+y] = 'u';
    return (0);
}