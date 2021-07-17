/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** sgt
*/

#include "server.h"

/**
* @brief Get the freq.
*
* @param client Graphical client who launched the command.
* @param server Contains all information about the current game.
*/
void sgt(client_t *client, server_t *server)
{
    char *str = my_int_to_char(server->args.freq);

    my_strcat(&client->buffer, "sgt ");
    my_strcat(&client->buffer, str);
    my_strcat(&client->buffer, "\n");
    free(str);
}
