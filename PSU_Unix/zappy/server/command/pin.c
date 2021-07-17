/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** pin
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
* @brief Add number to a string.
*
* @param client Current client.
* @param num Number to add.
*/
static void add_pos(client_t *client, int num)
{
    char *str = my_int_to_char(num);

    my_strcat(&client->buffer, str);
    free(str);
}

/**
* @brief Create message who contains all ressources of tmp.
*
* @param tmp Client whom we want to know his ressources.
* @param client Current graphical client.
*/
static void send_inventory(client_t *tmp, client_t *client)
{
    my_strcat(&client->buffer, "pin ");
    add_pos(client, tmp->id);
    my_strcat(&client->buffer, " ");
    add_pos(client, tmp->x);
    my_strcat(&client->buffer, " ");
    add_pos(client, tmp->y);
    my_strcat(&client->buffer, " ");
    add_pos(client, tmp->food);
    my_strcat(&client->buffer, " ");
    add_pos(client, tmp->ressources.linemate);
    my_strcat(&client->buffer, " ");
    add_pos(client, tmp->ressources.deraumere);
    my_strcat(&client->buffer, " ");
    add_pos(client, tmp->ressources.sibur);
    my_strcat(&client->buffer, " ");
    add_pos(client, tmp->ressources.mendiane);
    my_strcat(&client->buffer, " ");
    add_pos(client, tmp->ressources.phiras);
    my_strcat(&client->buffer, " ");
    add_pos(client, tmp->ressources.thystame);
}

/**
* @brief Give the client's inventory informations to the current client.
*
* @param client Graphical client who launched the command.
* @param server Contains all informations about the current game.
*/
void pin(client_t *client, server_t *server)
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
            send_inventory(cli, client);
            my_strcat(&client->buffer, "\n");
            return free_array(array);
        }
    }
    error_case(client, array);
}
