/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** cooldown_gestion
*/

#include "server.h"

/**
* @brief Return the cooldown of the given command.
*
* @param str Command.
* @return float
*/
float command_cooldown(char *str)
{
    char **array = NULL;
    int i = 0;

    if (!str)
        return 0;
    array = str_to_word_array(str, " ");
    if (!array || !array[0])
        return 0;
    else {
        for (; basic_command[i] &&
my_const_strcmp(array[0], basic_command[i]) != 0; ++i);
        if (my_const_strcmp(array[0], basic_command[i]) == 0) {
            free_array(array);
            return freq_basic_command[i];
        }
    }
    free_array(array);
    return 0;
}
