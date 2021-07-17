/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** my_strlen
*/

#include "server.h"

/**
* @brief Get string size.
*
* @param str String whom know the size.
* @return int
*/

int my_strlen(char *str)
{
    if (str == NULL)
        return 0;
    return strlen(str);
}
