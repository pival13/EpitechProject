/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** width
*/

#include "server.h"

/**
* @brief Get width given as argument.
*
* @param index The position of the arguments in the array.
* @param arg Array of arguments.
* @param server Contains all information about the current game.
* @return int
*/
int width(int index, char **arg, server_t *server)
{
    int new_index = index;
    server->args.width = 0;

    if (is_digit(arg[index + 1]))
        server->args.width = atoi(arg[index + 1]);
    else
        return -1;
    new_index += 1;
    return new_index;
}
