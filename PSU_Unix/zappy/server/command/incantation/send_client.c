/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** send_client
*/

#include "server.h"

/**
 * @brief Do nothing.
 *
 * @param client Current client.
 * @param server Contains all informations about the current game.
 */
void fakeincantation(__attribute__((unused)) client_t *client, \
__attribute__((unused)) server_t *server)
{
    return;
}

/**
* @brief Send string to all client that are concerned about the incantation.
*
* @param server Contains all informations about the current game.
* @param client Current client.
* @param value String to send to all concerned client.
*/

void send_to_all_concerned_client(server_t *server, client_t *client, \
char *value)
{
    client_t *cli = NULL;
    int size = server->map[client->y][client->x].nb_clients;
    char *str = NULL;

    for (int i = 0; i < size; ++i) {
        cli = found_client_with_fd(server, server->map\
[client->y][client->x].socket_list[i]);
        if (!cli)
            continue;
        if (cli->lvl == client->lvl) {
            my_strcat(&str, value);
            my_strcat(&cli->buffer, str);
            free(str);
            str = NULL;
        }
    }
}