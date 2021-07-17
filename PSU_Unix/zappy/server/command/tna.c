/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** tna
*/

#include "server.h"

/**
* @brief Send all team name to the current client.
*
* @param client Graphical client who launched the command.
* @param server Contains all informations about the current game.
*/
void tna(client_t *client, server_t *server)
{
    for (int i = 0; server->args.name[i]; ++i) {
        my_strcat(&client->buffer, "tna ");
        my_strcat(&client->buffer, server->args.name[i]);
        my_strcat(&client->buffer, "\n");
    }
}
