/*
** EPITECH PROJECT, 2019
** solver_test
** File description:
** solver without recur
*/

#include "dante.h"

static int is_good_cells(char *map, int x, int y, int size[2])
{
    if (y < 0 || x < 0 || y >= size[1] || x >= size[0])
        return (0);
    if (map[y*(size[0]+1)+x] == '*')
        return (1);
    return (0);
}

int move_back(char *map, int *x, int *y, int size[2])
{
    int a = 0;

    map[(*y)*(size[0]+1)+(*x)] = 'u';
    if (a == 0 && (*x+1) < size[0] && map[(*y)*(size[0]+1)+(*x)+1] == 'o') {
        *x += 1;
        a = 1;
    } else if (a == 0 && *y+1 < size[1] && map[(*y+1)*(size[0]+1)+*x] == 'o') {
        *y += 1;
        a = 1;
    }
    if (a == 0 && (*x-1) >= 0 && map[(*y)*(size[0]+1)+(*x)-1] == 'o') {
        *x -= 1;
        a = 1;
    } else if (a == 0 && (*y-1) >= 0 && map[(*y-1)*(size[0]+1)+(*x)] == 'o') {
        *y -= 1;
        a = 1;
    }
    if (a == 0)
        return (0);
    return (1);
}

int check_each_cell(char *map, int *i, int *j, int size[2])
{
    int a = 0;

    if (a == 0 && is_good_cells(map, *i+1, *j, size)) {
        *i += 1;
        a = 1;
    } else if (a == 0 && is_good_cells(map, *i, *j+1, size)) {
        *j += 1;
        a = 1;
    }
    if (a == 0 && is_good_cells(map, *i-1, *j, size)) {
        *i -= 1;
        a = 1;
    } else if (a == 0 && is_good_cells(map, *i, *j-1, size)) {
        *j -= 1;
        a = 1;
    }
    if (a == 0)
        return (move_back(map, i, j, size));
    return (1);
}

int solved_test(char *map, int size[2])
{
    int i = 0;
    int j = 0;

    while (map[j*(size[0]+1)+i+1] != '\0') {
        map[j*(size[0]+1)+i] = 'o';
        if (!check_each_cell(map, &i, &j, size))
            return (0);
    }
    map[j*(size[0]+1)+i] = 'o';
    clean_map(map);
    return (1);
}
