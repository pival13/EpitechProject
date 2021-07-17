/*
** EPITECH PROJECT, 2019
** is_end.c
** File description:
** is_end func to check if game is ended
*/

#include "navy.h"
#include "my.h"

int is_end(arrays_t **arrays)
{
    (*arrays)->nb_deaths = 0;
    (*arrays)->nb_kills = 0;
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if ((*arrays)->p1[i][j] == 'x')
                (*arrays)->nb_deaths += 1;
            if ((*arrays)->p2[i][j] == 'x')
                (*arrays)->nb_kills += 1;
        }
    }
    if ((*arrays)->nb_deaths >= 14)
        return (1);
    else if ((*arrays)->nb_kills >= 14)
        return (2);
    else return (0);
}
