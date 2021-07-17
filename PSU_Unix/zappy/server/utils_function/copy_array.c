/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** copy_array
*/

#include "server.h"

/**
* @brief Copy original float array to a new one.
*
* @param new Float array to copy.
* @return float *
*/

float *copy_array(float *new)
{
    float *result = malloc(sizeof(float) * 3);

    for (int i = 0; i <= 2; ++i)
        result[i] = new[i];
    return result;
}
