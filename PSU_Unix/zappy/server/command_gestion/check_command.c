/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** check_command
*/

#include "server.h"

static bool verify_command_exist_player(char **array)
{
    for (int i = 0; graphic_command[i]; ++i)
        if (my_const_strcmp(array[0], graphic_command[i]) == 0) {
            free_array(array);
            return true;
        }
    free_array(array);
    return false;
}

/**
* @brief Check if the command exist.
*
* @param str String given by the user.
* @param graphic True if the client is graphical, otherwise set at false.
* @return true
* @return false
*/
bool verify_command_exist(char *str, bool graphic)
{
    char **array = NULL;

    if (!str)
        return false;
    array = str_to_word_array(str, " ");
    if (array == NULL || array[0] == NULL)
        return false;
    for (int i = 0; basic_command[i]; ++i)
        if (my_const_strcmp(array[0], basic_command[i]) == 0) {
            free_array(array);
            return true;
        }
    if (!graphic) {
        free_array(array);
        return false;
    }
    return verify_command_exist_player(array);
}
