/*
** EPITECH PROJECT, 2018
** my_sokoban_next
** File description:
** Contain some functions of my_sokoban
*/

#include "my.h"
#include <ncurses.h>
#include <fcntl.h>
#include <stdlib.h>
#include "sokoban.h"

int check_map_next(char **map, int i, int j, int **pos_o)
{
    int compteur = 0;
    int if_o = 0;

    IF_BOX_IS_BLOCK {
        for (int k = 0; pos_o[k] != NULL; k++)
            if (pos_o[k][0] == i && pos_o[k][1] == j)
                if_o++;
        if (if_o == 0) {
            endwin();
            exit(1);
        }
    }
    for (int k = 0; pos_o[k] != NULL; k++)
        if (pos_o[k][0] == i && pos_o[k][1] == j && map[i][j] == 'X')
            compteur++;
    return (compteur);
}

void check_map(char **map, int **pos_o)
{
    int compteur = 0;
    int k = 1;

    for (k = 1; pos_o[k] != NULL; k++);
    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j] != '\0'; j++) {
            compteur += check_map_next(map, i, j, &pos_o[1]);
        }
    if (compteur == k - 1) {
        free_all(pos_o, map);
        my_putstr("Congratulations!\n");
        exit(0);
    }
}

void change_map2(char **map, int i, int x, int y)
{
    if (CAN_MOVE_BOX(KEY_UP, map[x-1][y], map[x-2][y])) {
        map[x][y] = ' ';
        map[x-2][y] = 'X';
        map[x-1][y] = 'P';
    }
    if (CAN_MOVE_BOX(KEY_DOWN, map[x+1][y], map[x+2][y])) {
        map[x][y] = ' ';
        map[x+2][y] = 'X';
        map[x+1][y] = 'P';
    }
    if (CAN_MOVE_BOX(KEY_RIGHT, map[x][y+1], map[x][y+2])) {
        map[x][y] = ' ';
        map[x][y+2] = 'X';
        map[x][y+1] = 'P';
    }
    if (CAN_MOVE_BOX(KEY_LEFT, map[x][y-1], map[x][y-2])) {
        map[x][y] = ' ';
        map[x][y-2] = 'X';
        map[x][y-1] = 'P';
    }
}

void change_map3(char **map, int i, int x, int y)
{
    if (CAN_MOVE_BOX('z', map[x-1][y], map[x-2][y])) {
        map[x][y] = ' ';
        map[x-2][y] = 'X';
        map[x-1][y] = 'Q';
    }
    if (CAN_MOVE_BOX('s', map[x+1][y], map[x+2][y])) {
        map[x][y] = ' ';
        map[x+2][y] = 'X';
        map[x+1][y] = 'Q';
    }
    if (CAN_MOVE_BOX('d', map[x][y+1], map[x][y+2])) {
        map[x][y] = ' ';
        map[x][y+2] = 'X';
        map[x][y+1] = 'Q';
    }
    if (CAN_MOVE_BOX('q', map[x][y-1], map[x][y-2])) {
        map[x][y] = ' ';
        map[x][y-2] = 'X';
        map[x][y-1] = 'Q';
    }
}

void change_map(char **map, int i, int **pos_o, int nb_j)
{
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;

    get_player(&x1, &y1, map, 'P');
    MOVE_DOWN(KEY_DOWN, x1, y1, 'P');
    MOVE_UP(KEY_UP, x1, y1, 'P');
    MOVE_RIGHT(KEY_RIGHT, x1, y1, 'P');
    MOVE_LEFT(KEY_LEFT, x1, y1, 'P');
    change_map2(map, i, x1, y1);
    if (nb_j != 1) {
        get_player(&x2, &y2, map, 'Q');
        MOVE_DOWN('s', x2, y2, 'Q');
        MOVE_UP('z', x2, y2, 'Q');
        MOVE_RIGHT('d', x2, y2, 'Q');
        MOVE_LEFT('q', x2, y2, 'Q');
        change_map3(map, i, x2, y2);
    }
    draw_o(map, &pos_o[1]);
}
