/*
** EPITECH PROJECT, 2019
** prepare_map
** File description:
** prepare the board
*/

#include <stdlib.h>

char **prepare_map(int size)
{
    char **map = malloc(sizeof(char *) * (size + 3));
    for (int i = 0; i < size + 2; i++)
        map[i] = malloc(sizeof(char) * (size * 2 + 2));
    for (int i = 0; i < size * 2 + 1; i++) {
        map[0][i] = '*';
        map[size+1][i] = '*';
    }
    for (int i = 1; i < size +1; i++) {
        map[i][0] = '*';
        for (int j = 1; j < size * 2; j++)
            if (j < size + i && j > size - i)
                map[i][j] = '|';
            else
                map[i][j] = ' ';
        map[i][size * 2] = '*';
    }
    for (int i = 0; i != size + 2; i++)
        map[i][size * 2 + 1] = '\n';
    map[size+2] = NULL;
    return (map);
}
