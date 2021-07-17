/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** sst
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
* @brief Change the current freq.
*
* @param client Graphical client who launched the command.
* @param server Contains all informations about the current games.
*/
void sst(client_t *client, server_t *server)
{
    char *str = NULL;
    char **array = str_to_word_array(client->readbuffer, " ");
    int new_time = 0;

    if (!array || size_array(array) < 2 || is_digit(array[1]) == false)
        return error_case(client, array);
    new_time = atoi(array[1]);
    if (new_time <= 0)
        return error_case(client, array);
    server->args.freq = new_time;
    str = my_int_to_char(server->args.freq);
    my_strcat(&client->buffer, "sst ");
    my_strcat(&client->buffer, str);
    my_strcat(&client->buffer, "\n");
    free(str);
    free_array(array);
}
