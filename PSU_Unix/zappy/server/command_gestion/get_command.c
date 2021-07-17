/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** get_command
*/

#include "server.h"

/**
* @brief The function read on the client's socket.
*
* @param temp The client who sent a command request.
* @param server Contains all informations about the current game.
* @return false If the read value is negative or equal to zero.
* @return true
*/
static bool read_on_the_socket(client_t *tmp, server_t *server)
{
    if (FD_ISSET(tmp->socket, &(server->readfds))) {
        tmp->readbuffer = malloc(sizeof(char) * LIMIT_BUFFER + 2);
        memset(tmp->readbuffer, 0, LIMIT_BUFFER + 2);
        if (read(tmp->socket, tmp->readbuffer, LIMIT_BUFFER + 1) <= 0 || \
my_strlen(tmp->readbuffer) > LIMIT_BUFFER) {
            tmp->is_free = true;
            my_strcat(&tmp->buffer, "ko\n");
            return false;
        }
    }
    return true;
}

/**
* @brief Get the user command.
*
* @param server Contains all informations about the current game.
*/
void get_command(server_t *server)
{
    for (client_t *temp = server->client; temp != NULL; temp = temp->next) {
        if (read_on_the_socket(temp, server) == false)
            continue;
        handle_command(temp);
        if (temp->readbuffer != NULL)
            launch_command(&temp, server);
        free(temp->readbuffer);
        temp->readbuffer = NULL;
    }
}
