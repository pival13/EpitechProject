/*
** EPITECH PROJECT, 2019
** ellers
** File description:
** ellers
*/

#include "dante.h"

void convert_tab(int **nb_tab , int y, int x, char **tab)
{
    for (int i = 0; i < y; ++i)
        for (int j = 0; j < x; ++j)
            if (nb_tab[i][j] == -2)
                tab[i][j] = 'X';
            else
                tab[i][j] = '*';
}

static void last_line2(int **nb_tab, int y, int x)
{
    for (int j = 0; j < x - 2; j += 2) {
        if (nb_tab[y - 1][j] == nb_tab[y - 1][j + 2])
            nb_tab[y - 1][j + 1] = -2;
        else {
            change_int(nb_tab, y - 1, x, \
(int[2]){nb_tab[y - 1][j], nb_tab[y - 1][j + 2]});
            nb_tab[y - 1][j + 1] = nb_tab[y - 1][j];
        }
    }
}

static void last_line(int **nb_tab, int y, int x)
{
    if (y % 2 != 1) {
        for (int j = 0; j < x; ++j)
            if (nb_tab[y - 1][j] == 0)
                nb_tab[y - 1][j] = nb_tab[y-2][j];
        for (int j = 0; j < x - 2; j += 2)
            if (nb_tab[y-1][j] != nb_tab[y-1][j + 2]) {
                nb_tab[y-1][j + 1] = nb_tab[y-1][j];
                change_int(nb_tab, y - 1, x, \
(int[2]){nb_tab[y - 1][j], nb_tab[y - 1][j + 2]});
            }
        if (nb_tab[y-2][x-1] != -2 && nb_tab[y-1][x-2] != -2)
            nb_tab[y-2][x-1] = -2;
        nb_tab[y-1][x-1] = 1;
    } else
            last_line2(nb_tab, y, x);
}

int **initialize_int_tab(int y, int x, char **tab)
{
    int count = 1;
    int **nb_tab = malloc(sizeof(int *) * (y + 1));
    for (int i = 0; i != y; i++) {
        nb_tab[i] = malloc(sizeof(int) * (x + 1));
        for (int j = 0; j != x; ++j) {
            nb_tab[i][j] = 0;
            if (tab[i][j] == '.')
                nb_tab[i][j] = count++;
            if (tab[i][j] == 'X')
                nb_tab[i][j] = -2;
        }
    }
    return nb_tab;
}

void ellers(char **tab)
{
    int x = 0;
    int y = 0;

    for (; tab[y] != NULL; y++);
    for (; tab[0][x] != '\0'; x++);
    int **nb_tab = initialize_int_tab(y, x, tab);
    for (int i = 0; i < y - 1; ++i) {
        for (int j = 0; j < x; ++j) {
            if (i % 2 == 0 && j % 2 == 1)
                pair(nb_tab, i, j, x);
            else if (i % 2 == 1 && nb_tab[i][j] != -2)
                not_pair(nb_tab, x, i, j);
        }
    }
    last_line(nb_tab, y, x);
    convert_tab(nb_tab, y, x, tab);
}
