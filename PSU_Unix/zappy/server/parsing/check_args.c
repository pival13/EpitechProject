/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** check_args
*/

#include "server.h"

/**
* @brief Check if arguments given in paramater is available.
*
* @param server Contains all informations about the current game.
* @return int
*/
int check_args(server_t *server)
{
    if (server->args.freq == 0 || \
server->args.height == 0 || \
server->args.width == 0 || \
server->args.client_number == 0 || server->args.port == 0)
        return EXIT_FAILURE;
    if (size_array(server->args.name) == 0)
        return EXIT_FAILURE;
    server->refill_cooldown = REFILL / server->args.freq;
    return EXIT_SUCCESS;
}
