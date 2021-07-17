/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** add_command
*/

#include "server.h"

/**
* @brief Add the new command inside the command array.
*
* @param client Current client.
* @param server Contains all information about the current game.
*/
void add_command(client_t **client, server_t *server)
{
    if ((*client)->graphic)
        return launch_graphic_command(client, server);
    if (!verify_command_exist((*client)->readbuffer, (*client)->graphic)) {
        send_client((*client), "ko\n");
        return;
    }
    for (int i = 0; i < 10; ++i)
        if ((*client)->command_array[i] == NULL) {
            (*client)->command_array[i] = strdup((*client)->readbuffer);
            break;
        }
    if ((*client)->cooldown == 0 && (*client)->command_array[0] != NULL) {
        (*client)->cooldown = command_cooldown((*client)->command_array[0]) \
/ server->args.freq;
        if (strncmp((*client)->command_array[0], "Fork", 4) == 0)
            send_egg_laying(server, *client);
        else if (strncmp((*client)->command_array[0], "Incantation", 11) == 0)
            send_incantation_first_part(server, *client);
    }
}
