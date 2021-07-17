/*
** EPITECH PROJECT, 2019
** nb_row && nb_col
** File description:
** nb_roww && nb_col
*/

#include <stdlib.h>

int nb_row(char **arr)
{
    int j = 0;

    for (; arr != NULL && arr[j] != NULL; j++);
    return (j);
}
