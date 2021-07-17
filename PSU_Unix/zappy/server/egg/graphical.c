/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** graphical
*/

#include "server.h"

/**
* @brief Notify all the graphical client that an egg is dead.
*
* @param server Contains all informations about the current game.
* @param client Current client.
*/

void death_egg(server_t *server, client_t *client)
{
    char *str = NULL;
    char *number = my_int_to_char(client->id);

    my_strcat(&str, "ebo ");
    my_strcat(&str, number);
    my_strcat(&str, "\n");
    my_strcat(&str, "edi ");
    my_strcat(&str, number);
    my_strcat(&str, "\n");
    send_to_all_graphic(server->client, str);
    free(str);
    free(number);
}

/**
* @brief Send a message when an egg is being laid.
*
* @param server Contains all informations about the current game.
* @param client Current graphical client.
*/

void send_egg_laying(server_t *server, client_t *client)
{
    char *str = NULL;
    char *number = NULL;

    my_strcat(&str, "pfk ");
    number = my_int_to_char(client->id);
    my_strcat(&str, number);
    my_strcat(&str, "\n");
    send_to_all_graphic(server->client, str);
    free(str);
    free(number);
}
