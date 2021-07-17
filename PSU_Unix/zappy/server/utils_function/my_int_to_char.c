/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** my_int_to_char
*/

#include "server.h"

/**
* @brief Transform int to string.
*
* @param num Number about to be transform.
* @return char *
*/

char *my_int_to_char(int num)
{
    char *str = NULL;

    if (num < 0)
        return NULL;
    if (num != 0) {
        str = malloc(sizeof(char) * ((int)log10(num) + 2));
        memset(str, 0, (int)log10(num) + 2);
    } else {
        str = malloc(sizeof(char) * 2);
        memset(str, 0, 2);
    }
    sprintf(str, "%d", num);
    return str;
}
