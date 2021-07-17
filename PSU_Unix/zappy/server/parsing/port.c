/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** port
*/

#include "server.h"

/**
* @brief Get port given as argument.
*
* @param index The position of the arguments in the array.
* @param arg Array of arguments.
* @param server Contains all information about the current game.
* @return int
*/
int port(int index, char **arg, server_t *server)
{
    int new_index = index;
    server->args.port = 0;

    if (is_digit(arg[index + 1]))
        server->args.port = atoi(arg[index + 1]);
    else
        return -1;
    new_index += 1;
    return new_index;
}
