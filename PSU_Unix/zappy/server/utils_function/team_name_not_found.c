/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** team_name_not_found
*/

#include "server.h"

/**
* @brief Check if team name is valid.
*
* @param str Team name.
* @param array Array of the valid team names.
* @return true Has not been found.
* @return false Has been found.
*/

bool team_name_not_found(char *str, char **array)
{
    if (str == NULL || array == NULL)
        return false;
    for (int i = 0; array[i]; ++i) {
        if (strcmp(array[i], str) == 0) {
            return false;
        }
    }
    return true;
}
