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
* @param str2 Second str.
* @return int
*/

int my_strcmp(char *str, char *str2)
{
    if (str == NULL || str2 == NULL)
        return -1;
    int len = strlen(str) > strlen(str2) ? strlen(str) : strlen(str2);
    for (int i = 0; i < len; ++i)
        if (str[i] != str2[i])
            return 1;
    return 0;
}
