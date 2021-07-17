/*
** EPITECH PROJECT, 2019
** hunt_kill
** File description:
** hunt and kill algo
*/

#include "dante.h"

int chose_cell(char **map, int *x, int *y)
{
    for (*y = 0; map[*y] != NULL; *y += 1)
        for (*x = 0; map[*y][*x] != '\0'; *x += 1) {
            if (map[*y][*x] == '.' && !is_good_cell(map, *x+2, *y))
                return (map[*y][*x+1] = '*');
            if (map[*y][*x] == '.' && !is_good_cell(map, *x-2, *y))
                return (map[*y][*x-1] = '*');
            if (map[*y][*x] == '.' && !is_good_cell(map, *x, *y+2))
                return (map[*y+1][*x] = '*');
            if (map[*y][*x] == '.' && !is_good_cell(map, *x, *y-2))
                return (map[*y-1][*x] = '*');
        }
    *x = rand() % ((*x + 1) / 2) * 2;
    *y = rand() % ((*y + 1) / 2) * 2;
    return (1);
}

void move_cell(char **map, int *x, int *y)
{
    int sx = *x;
    int sy = *y;

    do {
        *x = sx;
        *y = sy;
        if (rand() % 2 == 1)
            *x += rand() % 2 * 4 -2;
        else
            *y += rand() % 2 * 4 -2;
    } while (is_good_cell(map, *x, *y) != 1);
    if (*x == sx+2)
        map[sy][sx+1] = '*';
    if (*x == sx-2)
        map[sy][sx-1] = '*';
    if (*y == sy+2)
        map[sy+1][sx] = '*';
    if (*y == sy-2)
        map[sy-1][sx] = '*';
    map[*y][*x] = '*';
}

void create_wall(char **map)
{
    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j] != '\0'; j++)
            if (map[i][j] == ' ' && (is_good_cell(map, j-1, i) != 1 && is_go\
od_cell(map, j, i+1) != 1 && is_good_cell(map, j, i-1) != 1 && is_good_ce\
ll(map, j+1, i) != 1))
                map[i][j] = 'X';
}

void hunt_kill(char **map)
{
    int x;
    int y;

    while (!is_completed(map)) {
        if (chose_cell(map, &x, &y))
            map[y][x] = '*';
        while (!is_block(map, x, y)) {
            move_cell(map, &x, &y);
        }
        create_wall(map);
    }
    last_line_hk(map);
}