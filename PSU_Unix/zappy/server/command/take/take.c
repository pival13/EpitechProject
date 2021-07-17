/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** take
*/

#include "server.h"

/**
* @brief Send string to client.
*
* @param client Current client.
* @param str String to send to the client.
*/
void send_client(client_t *client, char *str)
{
    my_strcat(&client->buffer, str);
}

/** @brief Check if the given name is valid.
*
* @param str Name given by the client.
* @return int
*/
static int recognize_ressources(char *str)
{
    for (int i = 0; ressources[i]; ++i)
        if (strcmp(str, ressources[i]) == 0)
            return 0;
    return EXIT_FAILURE;
}

/**
* @brief Take object which on the ground.
*
* @param client Client who launched the command.
* @param server Contains all informations about the current game.
*/
void take(client_t *client, server_t *server)
{
    char **array = str_to_word_array(client->command_array[0], " ");

    if (!array || size_array(array) < 2) {
        free_array(array);
        send_client(client, "ko\n");
        return;
    }
    if (recognize_ressources(array[1]) == EXIT_FAILURE) {
        free_array(array);
        send_client(client, "ko\n");
        return;
    }
    take_ressources(client, server, array[1]);
    free_array(array);
}
