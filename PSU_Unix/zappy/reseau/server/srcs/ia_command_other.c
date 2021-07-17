/*
** EPITECH PROJECT, 2020
** Created by theo on 19/06/2020.
** File description:
** ia_command_other.c
*/

#include "rfc_ia.h"

player_t *start_send(player_t *client, __attribute__((unused))game_t **game)
{
    int size = my_strlen(client->pile->command);

    client->response = my_malloc(size - 5);
    for (int i = 6; i < size; i++)
        client->response[i - 6] = client->pile->command[i];
    client->response[size - 6] = '\0';
    return client;
}

player_t *message(player_t *client, __attribute__((unused))game_t **game)
{
    int size = my_strlen(client->pile->command);

    client->response = my_malloc(size + 1);
    client->response = strcpy(client->response, client->pile->command);
    client->response[size] = '\0';
    return client;
}

player_t *unknow_command(player_t *client,
    __attribute__((unused))game_t **game)
{
    client->response = NULL;
    client->response = my_strcat_second(client->response, "Wrong command: \0");
    client->response = my_strcat_second(client->response, client->pile->command);
    return client;
}

player_t *buffer_error(player_t *client, __attribute__((unused))game_t **game)
{
    client->response = my_malloc(28);
    client->response = strcpy(client->response,
        "WARNING: too longer buffer\n");
    return client;
}