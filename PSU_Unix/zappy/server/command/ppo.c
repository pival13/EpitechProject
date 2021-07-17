/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** ppo
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
* @brief If an error has occured send error.
*
* @param client Current client.
* @param array Contains command which has been split into words.
*/
static void add_pos(client_t *client, int num)
{
    char *str = my_int_to_char(num);

    my_strcat(&client->buffer, str);
    free(str);
}

/**
* @brief Send the specified client's position to the current one.
*
* @param tmp Specified client.
* @param client Current client.
*/
static void send_position(client_t *tmp, client_t *client)
{
    my_strcat(&client->buffer, "ppo ");
    add_pos(client, tmp->id);
    my_strcat(&client->buffer, " ");
    add_pos(client, tmp->x);
    my_strcat(&client->buffer, " ");
    add_pos(client, tmp->y);
    my_strcat(&client->buffer, " ");
    switch (tmp->direc) {
    case UP:
        return add_pos(client, 1);
    case RIGHT:
        return add_pos(client, 2);
    case DOWN:
        return add_pos(client, 3);
    default:
        return add_pos(client, 4);
    }
}

/**
* @brief Get the current positon of the player.
*
* @param client Client whom we want to know his position.
* @param server Contains all informations about the current game.
*/
void ppo(client_t *client, server_t *server)
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
            send_position(cli, client);
            my_strcat(&client->buffer, "\n");
            return free_array(array);
        }
    }
    error_case(client, array);
}
