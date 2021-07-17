/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** size_array
*/

#include "server.h"

/**
* @brief Determine the size of char * array.
*
* @param array char * array on which we want to know the size.
* @return size_t
*/

size_t size_array(char **array)
{
    size_t size = 0;

    if (array == NULL)
        return 0;
    for (size_t i = 0; array[i] != NULL; ++i, ++size);
    return size;
}
