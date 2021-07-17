/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** delete
*/

#include "server.h"

/**
* @brief Free server.
*
* @param server Contains all informations about the current game.
*/

void free_struct(server_t *server)
{
    free_link_list(server, true);
    delete_egg(server->egg, &server->egg, true);
    free(server->client);
    free_array(server->args.name);
    free_map(server);
    if (server->json)
        free_json(server->json);
}
