/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** pars_get_number
*/

#include "server.h"

/**
 * @brief Take Default value.
 *
 * @param server Contains all informations about the current game.
 */
void pars_get_number(server_t *server, json_t *json)
{
    server->args.freq = (int)json_get_number(json_get_with_key(server->json, \
"defaultFrequence"));
    server->args.client_number = (int)json_get_number(json_get_with_key(json, \
"playersByTeam"));
    server->args.height = (int)json_get_number(json_get_with_key(json, \
"height"));
    server->args.width = (int)json_get_number(json_get_with_key(json, \
"width"));
    server->args.port = (int)json_get_number(json_get_with_key(json, \
"port"));
}