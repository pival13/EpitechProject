/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** life_gestion
*/

#include "server.h"

/**
* @brief Send dead client informations to all graphical clients.
*
* @param server Contains all informations about the current game.
* @param client Client dead.
*/
static void send_death_to_graphic(server_t *server, client_t *client)
{
    char *str = NULL;
    char *number = NULL;

    my_strcat(&str, "pdi ");
    number = my_int_to_char(client->id);
    my_strcat(&str, number);
    my_strcat(&str, "\n");
    send_to_all_graphic(server->client, str);
    free(number);
    free(str);
}

/**
* @brief Decreases the user's life over time.
*
* @param server Contains all informations about the current game.
* @param client Client about to be life decreases.
*/
void life_gestion(server_t *server, client_t *client)
{
    if (client->graphic == true || client->is_connect == false)
        return;
    if (server->time .tv_usec == 0)
        client->food_time += 1.f / server->args.freq;
    if (client->food_time >= 126.f / server->args.freq) {
        client->food -= 1;
        client->food_time = 0;
        if (client->food <= 0) {
            send_death_to_graphic(server, client);
            my_strcat(&client->buffer, "dead\n");
            client->is_free = true;
        }
    }
}
