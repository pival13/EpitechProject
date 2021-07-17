/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send_to_all_graphic
*/

#include "server.h"

/**
*  @brief Send messages to all the graphical clients.
*
* @param client Link list of client.
* @param str String to send.
*/

void send_to_all_graphic(client_t *client, char *str)
{
    for (client_t *cli = client; cli; cli = cli->next)
        if (cli->graphic)
            my_strcat(&cli->buffer, str);
}