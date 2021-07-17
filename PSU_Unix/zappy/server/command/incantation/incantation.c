/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** incantation
*/

#include "server.h"

/**_
* @brief Find client by comparing his fd with the given one.
*
* @param server Contains all informations about the current game.
* @param fd Client's file descriptor.
* @return client_t *
*/
client_t *found_client_with_fd(server_t *server, int fd)
{
    for (client_t *cli = server->client; cli; cli = cli->next)
        if (fd == cli->socket)
            return cli;
    return NULL;
}

/**
* @brief Delete ressources needed to make the incantation.
*
* @param server Contains all the informations about the current game.
* @param y Y position of the current client.
* @param x X position of the current client.
* @param level Current level of the player that executed the incantation.
*/
static void delete_ressource_from_map(server_t *server, int y, int x, \
int level)
{
    json_t *json = json_get_with_key(server->json, "elevationPath");

    server->map[y][x].ressources.linemate -= json_get_number(json_get_with_key\
(json_get_at_index(json, level), "linemate"));
    server->map[y][x].ressources.deraumere -= json_get_number(json_get_with_\
key(json_get_at_index(json, level), "deraumere"));
    server->map[y][x].ressources.mendiane -= json_get_number(json_get_with_key\
(json_get_at_index(json, level), "mendiane"));
    server->map[y][x].ressources.phiras -= json_get_number(json_get_with_key\
(json_get_at_index(json, level), "phiras"));
    server->map[y][x].ressources.sibur -= json_get_number(json_get_with_key\
(json_get_at_index(json, level), "sibur"));
    server->map[y][x].ressources.thystame -= json_get_number(json_get_with_key\
(json_get_at_index(json, level), "thystame"));
}

/**
* @brief Send the current level after elevation, to all clients who
*  participated.
*
* @param server Contains all informations about the current game.
* @param y X position of the current client.
* @param x Y position of the current client.
* @param level Level of the current client.
*/
static void send_invocation_client(server_t *server, client_t *client)
{
    json_t *json = json_get_with_key(server->json, "elevationPath");
    int nb_player = json_get_number(json_get_with_key(json_get_at_index\
(json, client->lvl - 1), "player"));

    bc_send_invocation_client(server, client, nb_player);
    for (int k = 0; k < 6; ++k)
        client->incantation[k] = 0;
    delete_ressource_from_map(server, client->y, client->x, client->lvl - 1);
    end_of_game(server);
}

/**
* @brief Send result of the incantation to all the graphical's client.
*
* @param server Contains all the informations about the current game.
* @param client Current client.
* @param result Result of the incantation. Either 1 or 0.
*/
static void send_result_incantation_client(server_t *server, client_t \
*client, int result)
{
    char *str = strdup("pie ");
    char *number = my_int_to_char(client->x);

    my_strcat(&str, number);
    my_strcat(&str, " ");
    free(number);
    number = my_int_to_char(client->y);
    my_strcat(&str, number);
    my_strcat(&str, " ");
    free(number);
    number = my_int_to_char(result);
    my_strcat(&str, number);
    my_strcat(&str, "\n");
    send_to_all_graphic(server->client, str);
    if (result == 0)
        send_to_all_concerned_client(server, client, "ko\n");
    free(str);
    free(number);
}

/**
* @brief Increase the level of those who participate in the elevation.
*
* @param client Client who launched the command.
* @param server Contains all informations about the current game.
*/
void incantation(client_t *client, server_t *server)
{
    if (!verify_all_key(server, client)) {
        return send_result_incantation_client(server, client, 0);
    }
    if (!new_prerequisite(server, client, json_get_with_key(server->json, \
"elevationPath"), client->lvl - 1)) {
        return send_result_incantation_client(server, client, 0);
        }
    else {
        send_invocation_client(server, client);
        send_result_incantation_client(server, client, 1);
    }
}
