/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** how_many_in_the_time
*/

#include "server.h"

/**
* @brief Check the number of people whom have the same team name.
*
* @param server Contains all the informations about the current game.
* @param client Current client.
* @return ssize_t
*/

int hmitt(server_t *server, client_t *client)
{
    int nb_people_connect = 0;
    int nb_egg = 0;

    if (is_equal(client->team_name, GRAPHIC_NAME) == true)
        return 1;
    for (client_t *tmp = server->client; tmp != NULL; tmp = tmp->next)
        if (is_equal(tmp->team_name, client->team_name) == true && !tmp->egg)
            ++nb_people_connect;
    for (egg_t *tmp = server->egg; tmp != NULL; tmp = tmp->next)
        if (is_equal(tmp->team_name, client->team_name) == true && \
tmp->cooldown == -1)
            ++nb_egg;
    return server->args.client_number + nb_egg - nb_people_connect;
}
