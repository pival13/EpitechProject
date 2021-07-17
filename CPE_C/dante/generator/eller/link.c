/*
** EPITECH PROJECT, 2019
** link
** File description:
** link
*/

#include "dante.h"

void change_int(int **tab, int floor, int x, int *nb)
{
    for (int i = 0; i < x; ++i)
    {
        if (tab[floor][i] == nb[1])
            tab[floor][i] = nb[0];
    }
}

int future_link(int **tab, int *floor, int x, int nb)
{
    for (int i = floor[1]; i < x; i++) {
        if (tab[floor[0]][i] == nb && tab[floor[0] - 1][i] == nb)
            return 1;
    }
    return 0;
}

int has_link(int **tab, int floor, int x, int nb)
{
    for (int i = 0; i < x; i++) {
        if (tab[floor][i] == nb && tab[floor - 1][i] == nb)
            return 1;
    }
    return 0;
}

void not_pair(int **nb_tab, int x, int i, int j)
{
    if (!has_link(nb_tab, i, x, nb_tab[i-1][j]) && \
!future_link(nb_tab, (int[2]){i, j}, x, nb_tab[i-1][j])) {
        nb_tab[i][j] = nb_tab[i - 1][j];
        nb_tab[i + 1][j] = nb_tab[i - 1][j];
    } else {
        if (rand() % 2 == 0) {
            nb_tab[i][j] = nb_tab[i - 1][j];
            nb_tab[i + 1][j] = nb_tab[i - 1][j];
        } else
            nb_tab[i][j] = -2;
    }
}

void pair(int **nb_tab, int i, int j, int x)
{
    if (nb_tab[i][j - 1] == nb_tab[i][j + 1])
        nb_tab[i][j] = -2;
    else {
        if (rand() % 2 == 0)
            nb_tab[i][j] = -2;
        else {
            change_int(nb_tab, i, x, (int[2]){nb_tab[i][j - 1], \
nb_tab[i][j + 1]});
            nb_tab[i][j] = nb_tab[i][j - 1];
        }
    }
}