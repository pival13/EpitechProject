/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** my_strcmp
*/

#include "server.h"

/**
* @brief Compare two strings.
*
* @param str First str.
* @param str2 Second const str.
* @return int
*/

int my_const_strcmp(char *str, const char *str2)
{
    if (!str || !str2)
        return 1;
    return strcmp(str, str2);
}
