/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** prerequisite
*/

#include "server.h"

static bool new_psl(server_t *server, client_t *client)
{
    json_t *json = json_get_with_key(server->json, "elevationPath");
    client_t *cli = NULL;
    int nb_player = json_get_number(json_get_with_key(json_get_at_index\
(json, client->lvl - 1), "player"));
    int go = 0;

    for (int i = 0; i < nb_player; ++i) {
        cli = found_client_with_fd(server, client->incantation[i]);
        if (cli && cli->is_connect && cli->is_incantating && !cli->is_free)
            ++go;
    }
    if (go == nb_player) {
        return true;
    } else {
        return false;
    }
    return false;
}

/**
* @brief Check if there are enough AI of the same level to elevate themself.
*
* @param server Contains all infomation about the current game.
* @param map The current map case.
* @param nplayer The number of player inside current map case.
* @param level The level of the current client.
* @return true
* @return false
*/
static bool psl(server_t *server, map_t map, int nplayer, int level)
{
    client_t *cli = NULL;
    int go = 0;

    for (int i = 0; i < map.nb_clients; ++i) {
        cli = found_client_with_fd(server, map.socket_list[i]);
        if (!cli || cli->is_incantating)
            continue;
        if (cli->lvl == level)
            ++go;
    }
    if (go >= nplayer) {
        return true;
    } else {
        return false;
    }
    return false;
}

bool new_prerequisite(server_t *server, client_t *client, json_t *json, \
int level)
{
    if (server->map[client->y][client->x].ressources.deraumere >= \
json_get_number(json_get_with_key(json_get_at_index(json, level), \
"deraumere")) && server->map[client->y][client->x].ressources.linemate >= \
json_get_number(json_get_with_key(json_get_at_index(json, level), \
"linemate")) && server->map[client->y][client->x].ressources.mendiane >= \
json_get_number(json_get_with_key(json_get_at_index(json, level), \
"mendiane"))) {
        if (server->map[client->y][client->x].ressources.phiras >= \
json_get_number(json_get_with_key(json_get_at_index(json, level), \
"phiras")) && server->map[client->y][client->x].ressources.sibur >= \
json_get_number(json_get_with_key(json_get_at_index(json, level), \
"sibur")) && server->map[client->y][client->x].ressources.thystame >= \
json_get_number(json_get_with_key(json_get_at_index(json, level), \
"thystame")))
            return new_psl(server, client);
    }
    return false;
}

/**
* @brief Check if client can make an incantation.
*
* @param server Contains all informations about the current game.
* @param client Current client.
* @param json Information about the elevation's prerequisite.
* @param level Current client's level.
* @return true
* @return false
*/
bool prerequisite(server_t *server, client_t *client, json_t *json, int level)
{
    int nplayer = json_get_number(json_get_with_key(json_get_at_index\
(json, level), "player"));

    if (server->map[client->y][client->x].nb_clients >= nplayer && \
server->map[client->y][client->x].ressources.deraumere >= json_get_number\
(json_get_with_key(json_get_at_index(json, level), "deraumere")) && \
server->map[client->y][client->x].ressources.linemate >= json_get_number\
(json_get_with_key(json_get_at_index(json, level), "linemate")) && \
server->map[client->y][client->x].ressources.mendiane >= json_get_number\
(json_get_with_key(json_get_at_index(json, level), "mendiane"))) {
        if (server->map[client->y][client->x].ressources.phiras >= \
json_get_number(json_get_with_key(json_get_at_index(json, level), \
"phiras")) && server->map[client->y][client->x].ressources.sibur >= \
json_get_number(json_get_with_key(json_get_at_index(json, level), \
"sibur")) && server->map[client->y][client->x].ressources.thystame >= \
json_get_number(json_get_with_key(json_get_at_index(json, level), \
"thystame")))
            return psl(server, server->map[client->y][client->x], nplayer, \
client->lvl);
    }
    return false;
}