/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** graphicals
*/

#include "server.h"

/**
* @brief Launch graphical client if it exists.
*
* @param client Current clients.
* @param server Contains all informations about the current game.
*/
void launch_graphic_command(client_t **client, server_t *server)
{
    char **array = str_to_word_array((*client)->readbuffer, " ");

    for (int i = 0; array && array[0] && graphic_command[i]; ++i)
        if (strcmp(graphic_command[i], array[0]) == 0) {
            command_server[i + 13]((*client), server);
            free_array(array);
            return;
        }
    free_array(array);
    my_strcat(&(*client)->buffer, "suc\n");
}
