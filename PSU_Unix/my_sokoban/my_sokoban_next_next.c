/*
** EPITECH PROJECT, 2018
** my_sokoban_next_next
** File description:
** Contain the last functions of my_sokoban
*/

#include <ncurses.h>
#include "my.h"
#include "sokoban.h"
#include <stdlib.h>

void check_size(int **size, char **map)
{
    char *str = "Please, enlarge the window.";

    while (LINES < size[0][0] || COLS < size[0][1]) {
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(LINES/2, COLS/2 - my_strlen(str)/2, str);
        attroff(COLOR_PAIR(1));
        refresh();
        if (getch() == ' ') {
            free_all(size, map);
            exit(0);
        }
    }
}

void display_with_color(char **map, int *pos)
{
    for (int j = 0; map[j] != NULL; j++)
        for (int i = 0; map[j][i] != '\n' && map[j][i] != '\0'; i++) {
            DRAW('#', '#', 3);
            DRAW('O', 'O', 2);
            DRAW('P', 'P', 4);
            DRAW('Q', 'P', 5);
            DRAW('X', 'X', 1);
        }
}

int make_game(char **map, int **pos_o, int i, int nb_j)
{
    check_size(pos_o, map);
    clear();
    change_map(map, i, pos_o, nb_j);
    display_with_color(map, pos_o[0]);
    refresh();
    check_map(map, pos_o);
    return (getch());
}

void get_player(int *x, int *y, char **map, char player)
{
    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j] != '\n'; j++)
            if (map[i][j] == player) {
                *x = i;
                *y = j;
            }
}

void draw_o(char **map, int **pos_o)
{
    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j] != '\n'; j++)
            for (int k = 0; pos_o[k] != NULL; k++)
                if (pos_o[k][0] == i && pos_o[k][1] == j && map[i][j] == ' ')
                    map[i][j] = 'O';
}
