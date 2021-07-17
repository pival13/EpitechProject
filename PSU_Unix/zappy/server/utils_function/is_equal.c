/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** is_equal
*/

#include "server.h"

/**
* @brief Check if two string are equal.
*
* @param str
* @param str2
* @return true
* @return false
*/

bool is_equal(char *str, char *str2)
{
    if (str == NULL || str2 == NULL)
        return false;
    if (strlen(str) != strlen(str2))
        return false;
    for (size_t i = 0; str[i] != '\0'; ++i)
        if (str[i] != str2[i])
            return false;
    return true;
}