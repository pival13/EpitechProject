/*
** EPITECH PROJECT, 2018
** invers
** File description:
** inverse a matrix
*/

#include <stdio.h>
#include <stdlib.h>
#define ARE_SAME(x, y) ((x == y) ? 1 : 0)

float invers(int **key, int x, int y, int d)
{
    if (d == 1)
        return (key[0][0]*key[x][y]-key[x][0]*key[0][y]);
    else if (d == 0)
        return (key[x][y]);
    else
        return (invers(key, d-1, d-1, d-1) * invers(key, x, y, d-1) - invers(key, x, d-1, d-1) * invers(key, d-1, y, d-1));
}

float inversr(int **key, int x, int y, int d)
{
    if (d == 1)
        return (key[0][0] * ARE_SAME(x, y) - key[x][0] * ARE_SAME(0, y));
    else if (d == 0)
        return (ARE_SAME(x, y));
    else
        return (invers(key, d-1, d-1, d-1) * inversr(key, x, y, d-1) - invers(key, x, d-1, d-1) * inversr(key, d-1, y, d-1)); 
}

float **matrice_invers(int **key)
{
    int size = 0;
    float **inv;
    int malus = 1;

    for (size = 0; key[size] != NULL; size++);
    inv = malloc(sizeof(int *) * (size + 1));
    for (int i = size-1; i >= 0; i--, malus++) {
        inv[i] = malloc(sizeof(int) * (size));
        for (int j = 0; j != size; j++) {
            inv[i][j] = 0;
            if (invers(key, size-malus, size-malus, size-malus) == 0)
                exit (84);
            inv[i][j] += inversr(key, i, j, size-malus);
            for (int k = size-1; k != i; k--)
                inv[i][j] -= inv[k][j]*invers(key, i, k, size-malus);
            inv[i][j] /= invers(key, size-malus, size-malus, size-malus);
        }
    }
    return (inv);
}
