/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** msz
*/

#include "server.h"

/**
* @brief Give the map's dimensions.
*
* @param client Graphical client who launched the command.
* @param server Contains all informations about the game.
*/
void msz(client_t *client, server_t *server)
{
    char *height = my_int_to_char(server->args.height);
    char *width = my_int_to_char(server->args.width);

    my_strcat(&client->buffer, "msz ");
    my_strcat(&client->buffer, width);
    my_strcat(&client->buffer, " ");
    my_strcat(&client->buffer, height);
    my_strcat(&client->buffer, "\n");
    free(height);
    free(width);
}
