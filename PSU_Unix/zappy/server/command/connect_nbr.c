/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** connect_nbr
*/

#include "server.h"

/**
* @brief return the unused slots number inside the team.
*
* @param client Player who execute the command.
* @param server Server contains all informations about the current game.
*/
void connect_nbr(client_t *client, server_t *server)
{
    char *str = my_int_to_char(hmitt(server, client));

    my_strcat(&str, "\n");
    my_strcat(&client->buffer, str);
    free(str);
}
