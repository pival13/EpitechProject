/*
** EPITECH PROJECT, 2018
** my_sokoban
** File description:
** A game of sokoban
*/

#include "my.h"
#include <ncurses.h>
#include <fcntl.h>
#include <stdlib.h>
#include "sokoban.h"

int **prepare_pos_o(char **map)
{
    int o = 0;
    int **pos_o;

    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j] != '\0'; j++)
            if (map[i][j] == 'O')
                o++;
    pos_o = malloc(sizeof(int *) * (o + 2));
    for (int i = 0; i != (o + 1); i++)
        pos_o[i] = malloc(sizeof(int) * 2);
    pos_o[0][1] = 0;
    for (pos_o[0][0] = 0; map[pos_o[0][0]] != NULL; pos_o[0][0]++)
        for (int j = 0; map[pos_o[0][0]][j] != '\0'; j++)
            if (j > pos_o[0][1])
                pos_o[0][1] = j;
    return (pos_o);
}

int **check_map_first(char **map, int nb_j)
{
    int nb_elem[3] = {0, 0, 0};
    int **pos_o = prepare_pos_o(map);

    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j] != '\0'; j++) {
            (nb_j == 1) ? (CHECK_CHAR) : (CHECK_CHAR_MULT);
            (map[i][j] == 'P') ? (nb_elem[0]++) : (nb_elem[0]);
            (nb_j == 2 && map[i][j] == 'Q') ? (nb_elem[0]++) : 0;
            (map[i][j] == 'X') ? (nb_elem[1]++) : (nb_elem[1]);
            if (map[i][j] == 'O') {
                nb_elem[2]++;
                pos_o[nb_elem[2]][0] = i;
                pos_o[nb_elem[2]][1] = j;
            }
        }
    pos_o[nb_elem[2]+1] = NULL;
    (nb_elem[0] != nb_j || nb_elem[1] != nb_elem[2]) ? exit(84) : 0;
    return (pos_o);
}

void free_all(int **pos_o, char **map)
{
    endwin();
    for (int i = 0; pos_o[i] != NULL; i++)
        free(pos_o[i]);
    for (int i = 0; map[i] != NULL; i++)
        free(map[i]);
    free(pos_o);
    free(map);
}

void init_window(void)
{
    initscr();
    start_color();
    init_pair(1, 15, 0);
    init_pair(2, COLOR_MAGENTA, 0);
    init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(4, 14, 0);
    init_pair(5, 10, 0);
    curs_set(false);
    keypad(stdscr, true);
}

int sokoban(char *arg, int nb_j)
{
    int i = 'a';
    char **map = load_2d_arr_from_file(arg);
    int **pos_o = check_map_first(map, nb_j);

    (pos_o[1] == NULL) ? exit(84) : 0;
    init_window();
    display_with_color(map, pos_o[0]);
    while (i != ' ') {
        i = make_game(map, pos_o, i, nb_j);
        (i == 'r') ? (map = load_2d_arr_from_file(arg)) : map;
    }
    free_all(pos_o, map);
}
