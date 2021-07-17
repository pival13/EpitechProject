/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** delete_map
*/

#include "server.h"

/**
* @brief Free the game map.
*
* @param server Contains all informations about the current game.
*/

void free_map(server_t *server)
{
    if (server->map == NULL)
        return;
    for (int i = 0; i < server->args.height; ++i) {
        for (int j = 0; j < server->args.width; ++j)
            server->map[i][j].socket_list != NULL && \
server->map[i][j].nb_clients > 0 ? free(server->map[i][j].socket_list) : 0;
        free(server->map[i]);
    }
    free(server->map);
}
