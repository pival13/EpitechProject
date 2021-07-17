/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** broadcast
*/

#include "server.h"

/**
* @brief Send a message to all players.
*
* @param client Player to execute the command.
* @param server Contains all informations about the current game.
*/
void broadcast(client_t *client, server_t *server)
{
    char *arg = get_text_to_broadcast(client->command_array[0]);
    char *message = NULL;
    char str[2];
    short dir = 0;

    for (client_t *tmp = server->client; tmp != NULL; tmp = tmp->next) {
        if (tmp->graphic == true || tmp->is_connect == false)
            continue;
        memset(str, 0, 2);
        dir = calc_direction(server, client, tmp);
        sprintf(str, "%d", dir);
        message = create_message(arg, str);
        send_broadcast(tmp, message, client->socket);
        free(message);
        message = NULL;
    }
    send_broadcast_to_graphic(server, client, arg);
    free(arg);
}
