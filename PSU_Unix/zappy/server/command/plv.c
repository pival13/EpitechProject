/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** plv
*/

#include "server.h"

/**
* @brief If an error has occured send error.
*
* @param client Current client.
* @param array Contains command which has been split into words.
*/
static void error_case(client_t *client, char **array)
{
    my_strcat(&client->buffer, "sbp\n");
    free_array(array);
}

/**
* @brief Send the level of the specified client to the current one.
*
* @param tmp Client whom we want to know his level.
* @param client Current graphical client.
*/
static void send_level(client_t *tmp, client_t *client)
{
    char *number = my_int_to_char(tmp->id);
    char *level = my_int_to_char(tmp->lvl);

    my_strcat(&client->buffer, "plv ");
    my_strcat(&client->buffer, number);
    my_strcat(&client->buffer, " ");
    my_strcat(&client->buffer, level);
    my_strcat(&client->buffer, "\n");
    free(number);
    free(level);
}

/**
* @brief Get the current level of the player.
*
* @param client Client whom we want to know his level.
* @param server Contains all informations about the current game.
*/
void plv(client_t *client, server_t *server)
{
    char **array = str_to_word_array(client->readbuffer, " ");
    int id = 0;

    if (!array || size_array(array) < 2 || is_digit(array[1]) == false)
        return error_case(client, array);
    id = atoi(array[1]);
    if (id <= 0)
        return error_case(client, array);
    for (client_t *cli = server->client; cli; cli = cli->next) {
        if (id == (int)cli->id) {
            send_level(cli, client);
            return free_array(array);
        }
    }
    error_case(client, array);
}
