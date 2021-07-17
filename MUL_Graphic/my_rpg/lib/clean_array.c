/*
** EPITECH PROJECT, 2019
** clean_array.c
** File description:
** clean array
*/

#include "my.h"

void clean_array(char **array)
{
    int y = my_arraylen(array);

    for (int i = 0; i < y; i++)
        clean_str(array[i]);
}
