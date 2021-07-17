/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** spawn_client
*/

#include "server.h"

/**
* @brief Add client inside cell of map.
*
* @param node Map cell to add a new client.
* @param fd Fd of current user.
*/
void add_client(map_t *node, int fd)
{
    int *tmp_array = NULL;
    int i = 0;

    if (node->nb_clients > 0) {
        tmp_array = malloc(sizeof(int) * (node->nb_clients + 1));
        for (; i < node->nb_clients; ++i)
            tmp_array[i] = node->socket_list[i];
        free(node->socket_list);
        node->nb_clients += 1;
    } else {
        tmp_array = malloc(sizeof(int) * 1);
        node->nb_clients = 1;
    }
    tmp_array[i] = fd;
    node->socket_list = tmp_array;
}

/**
* @brief Add the client to the random position on the game's map.
*
* @param server Contains all informations about the current game.
* @param client Client to add on the map.
*/
void spawn_client(server_t *server, client_t **client)
{
    map_t *node = NULL;
    int *tmp_array = NULL;
    int i = 0;

    (*client)->y = rand() % server->args.height;
    (*client)->x = rand() % server->args.width;
    (*client)->direc = rand() % 4;
    node = &server->map[(*client)->y][(*client)->x];
    if (node->nb_clients > 0) {
        tmp_array = malloc(sizeof(int) * (node->nb_clients + 1));
        for (; i < node->nb_clients; ++i)
            tmp_array[i] = node->socket_list[i];
        node->nb_clients += 1;
    } else {
        tmp_array = malloc(sizeof(int) * 1);
        node->nb_clients = 1;
    }
    tmp_array[i] = (*client)->socket;
    node->socket_list != NULL ? free(node->socket_list) : 0;
    node->socket_list = tmp_array;
}
