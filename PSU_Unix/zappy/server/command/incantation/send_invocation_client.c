/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send_invocation_client
*/

#include "server.h"

void bc_send_invocation_client(server_t *server, client_t *client, \
int nb_player)
{
    client_t *cli = NULL;
    char *str = NULL;
    char *number = NULL;

    for (int i = 0; i < nb_player; ++i) {
        cli = found_client_with_fd(server, client->incantation[i]);
        if (!cli)
            continue;
        ++cli->lvl;
        my_strcat(&str, "Current level: ");
        number = my_int_to_char(cli->lvl);
        my_strcat(&str, number);
        my_strcat(&str, "\n");
        my_strcat(&cli->buffer, str);
        free(str);
        str = NULL;
        free(number);
        cli->is_incantating = false;
    }
}