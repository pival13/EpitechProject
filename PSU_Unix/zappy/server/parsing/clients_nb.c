/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** clients_nb
*/

#include "server.h"

/**
* @brief Get max number.
*
* @param index The position of the arguments in the array.
* @param arg Array of arguments.
* @param server Contains all information about the current game.
* @return int
*/
int clients_nb(int index, char **arg, server_t *server)
{
    int new_index = index;
    server->args.client_number = 0;

    if (is_digit(arg[index + 1]))
        server->args.client_number = atoi(arg[index + 1]);
    else
        return -1;
    new_index += 1;
    return new_index;
}
