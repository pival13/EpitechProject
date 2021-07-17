/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** free_array
*/

#include "server.h"

/**
* @brief Free char * array given in param.
*
* @param array Char * array to be free.
*/

void free_array(char **array)
{
    if (array == NULL)
        return;
    for (size_t i = 0; array[i] != NULL; ++i)
        free(array[i]);
    free(array);
}
