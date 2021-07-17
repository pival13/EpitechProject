/*
** EPITECH PROJECT, 2019
** array.c
** File description:
** array funcs
*/

#include "navy.h"
#include "my.h"
#include <signal.h>
#include <stdlib.h>

arrays_t *replace_case(int range, int *order, arrays_t *arrays)
{
    int sens_h = 0;
    int sens_v = 0;

    if (order[0] == order[2])
        sens_v = 1;
    if (order[1] == order[3])
        sens_h = 1;
    if (sens_h == 0 && sens_v == 0)
        return (NULL);
    if (sens_h == 1 && order[0] + range - 1 != order[2])
        return (NULL);
    if (sens_v == 1 && order[1] + range - 1 != order[3])
        return (NULL);
    for (int i = 1, j = 0; i <= range; i++, j++) {
        arrays->p1[order[1] + sens_v * j][order[0] + sens_h * j] = range + 48;
    }
    return (arrays);
}

int error_arrays(char **pos)
{
    for (int i = 0; i <= 3; i++) {
        if (pos[i][1] != ':' || pos[i][4] != ':')
            return (84);
        if (pos[i][2] < 65 || pos[i][2] > 72 ||
            pos[i][5] < 65 || pos[i][2] > 72)
            return (84);
        if (pos[i][3] < 49 || pos[i][3] > 56 ||
            pos[i][6] < 49 || pos[i][6] > 56)
            return (84);
    }
    return (0);
}

arrays_t *trad_arrays(arrays_t *arrays, char **pos)
{
    int order[4];

    if (pos[0][0] != '2' || pos[1][0] != '3'
        || pos[2][0] != '4' || pos[3][0] != '5')
        return (NULL);
    if (error_arrays(pos) == 84)
        return (NULL);
    for (int i = 0; i <= 3; i++) {
        order[0] = pos[i][2] - 64;
        order[1] = pos[i][3] - 48;
        order[2] = pos[i][5] - 64;
        order[3] = pos[i][6] - 48;
        arrays = replace_case(i + 2, order, arrays);
        if (arrays == NULL)
            return (NULL);
    }
    return (arrays);
}

arrays_t *create_arrays(void)
{
    arrays_t *arrays = malloc(sizeof(arrays_t));

    arrays->p1 = malloc(sizeof(char *) * 12);
    arrays->p2 = malloc(sizeof(char *) * 12);
    for (int i = 0; i <= 10; i++) {
        arrays->p1[i] = malloc(sizeof(char) * 11);
        arrays->p2[i] = malloc(sizeof(char) * 11);
        arrays->p1[i+1] = NULL;
        arrays->p2[i+1] = NULL;
        for (int j = 0; j <= 8; j++) {
            arrays->p1[i][j] = '.';
            arrays->p2[i][j] = '.';
            arrays->p1[i][j+1] = 0;
            arrays->p2[i][j+1] = 0;
        }
    }
    arrays->nb_kills = 0;
    arrays->nb_deaths = 0;
    return (arrays);
}

void destroy_arrays(arrays_t *arrays)
{
    for (int i = 10; i >= 0; i--) {
        free(arrays->p1[i]);
        free(arrays->p2[i]);
    }
    free(arrays->p1);
    free(arrays->p2);
    free(arrays);
}
