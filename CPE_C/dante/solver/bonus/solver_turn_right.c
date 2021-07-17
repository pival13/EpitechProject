/*
** EPITECH PROJECT, 2019
** solver
** File description:
** solver of solver
*/

#include "dante.h"

int solved_wall2(solver_t *w, int pos[2], int prev[2], int len)
{
    w->map[pos[0]*w->len+pos[1]] = 'o';
    if (pos[0]*w->len + pos[1] + 1 == len) {
        w->finish = 1;
        return (1);
    }
    if (pos[0] == prev[0] && pos[1] == prev[1] + 1)
        return (solved_wall(w, (int [2]){pos[0]+1, pos[1]}, pos));
    if (pos[0] == prev[0] + 1 && pos[1] == prev[1])
        return (solved_wall(w, (int [2]){pos[0], pos[1]-1}, pos));
    if (pos[0] == prev[0] && pos[1] == prev[1] - 1)
        return (solved_wall(w, (int [2]){pos[0]-1, pos[1]}, pos));
    if (pos[0] == prev[0] - 1 && pos[1] == prev[1])
        return (solved_wall(w, (int [2]){pos[0], pos[1]+1}, pos));
    return (0);
}

int solved_wall(solver_t *w, int pos[2], int prev[2])
{
    int len = strlen(w->map);

    if (pos[0] == -1 && pos[1] == 0)
        return (0);
    if (pos[1] < 0 || pos[1] >= w->len-1 || pos[0] < 0 || pos[0]*w->len+pos[1] \
> len || w->map[pos[0]*w->len+pos[1]] == 'X') {
        if (pos[0] == prev[0] && pos[1] == prev[1] + 1)
            return (solved_wall(w, (int [2]){prev[0]-1, prev[1]}, prev));
        if (pos[0] == prev[0] + 1 && pos[1] == prev[1])
            return (solved_wall(w, (int [2]){prev[0], prev[1]+1}, prev));
        if (pos[0] == prev[0] && pos[1] == prev[1] - 1)
            return (solved_wall(w, (int [2]){prev[0]+1, prev[1]}, prev));
        if (pos[0] == prev[0] - 1 && pos[1] == prev[1])
            return (solved_wall(w, (int [2]){prev[0], prev[1]-1}, prev));
    }
    return (solved_wall2(w, pos, prev, len));
}