/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** is_digit
*/

#include "server.h"

/**
* @brief Determine if the given string contain only letter.
*
* @param str String about to be verify.
* @return true
* @return false
*/

bool is_digit(char *str)
{
    if (str == NULL)
        return false;
    for (size_t i = 0; str[i] != '\0'; ++i)
        if (str[i] < '0' || str[i] > '9')
            return false;
    return true;
}
