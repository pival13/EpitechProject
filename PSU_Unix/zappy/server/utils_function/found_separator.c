/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** found_separator
*/

#include "server.h"

/**
* @brief Check if the given separator is present inside the given string.
*
* @param str String about to be check.
* @param c Separator to find.
* @return true
* @return false
*/

bool found_separator(char *str, char c)
{
    for (size_t i = 0; str[i] != 0; ++i)
        if (str[i] == c)
            return true;
    return false;
}