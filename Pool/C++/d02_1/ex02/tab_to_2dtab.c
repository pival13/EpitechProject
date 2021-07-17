/*
** EPITECH PROJECT, 2020
** tab_to_2dtab.c
** File description:
** convert a tab to a 2d tab
*/

#include <stdlib.h>

void tab_to_2dtab(const int *tab, int length, int width, int ***res)
{
    if (length < 1 || width < 1 || tab == NULL)
        return;
    *res = malloc(sizeof(int *) * length);
    if (res == NULL)
        return;
    for (int i = 0; i != length; i++) {
        res[0][i] = malloc(sizeof(int) * width);
        if (res[0][i] == NULL) {
            for (int j = 0; j != i; j++)
                free(res[0][j]);
            free(*res);
        }
        for (int j = 0; j != width; j++)
            res[0][i][j] = tab[i*width+j];
    }
}