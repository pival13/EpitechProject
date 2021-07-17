/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send_answer
*/

#include "server.h"

/**
* @brief Cut the sended part of the message.
*
* @param client Current client.
* @param size Size of the cutted message.
*/
static void cut_useless_part_of_send(client_t *client, ssize_t size)
{
    char *tmp = malloc(sizeof(char) * (strlen(client->buffer) - size + 1));

    memset(tmp, 0, strlen(client->buffer) - size + 1);
    for (ssize_t i = 0, j = 0; client->buffer[i] != 0; ++i) {
        if (i >= size) {
            tmp[j] = client->buffer[i];
            ++j;
        }
    }
    free(client->buffer);
    client->buffer = NULL;
    client->buffer = strdup(tmp);
    free(tmp);
}

/**
 * @brief Check if the write has send all buffer.
 *
 * @param client Contains all informations about the current game.
 * @param size Size of write buffer which has been sent.
 */
static void check_write(client_t *client, ssize_t size)
{
    if (size <= 0) {
        client->is_free = true;
    } else if (size != (ssize_t)strlen(client->buffer)) {
        cut_useless_part_of_send(client, size);
    } else {
        free(client->buffer);
        client->buffer = NULL;
    }
}

/**
* @brief Write all clients messages.
*
* @param server Contains all informations about the current game.
*/
void write_all(server_t *server)
{
    ssize_t size = 0;

    for (client_t *tmp = server->client; tmp != NULL; tmp = tmp->next) {
        if (FD_ISSET(tmp->socket, &(server->writefds)) && \
tmp->buffer != NULL) {
            size = send(tmp->socket, tmp->buffer, strlen(tmp->buffer), \
MSG_NOSIGNAL);
            check_write(tmp, size);
        }
    }
    if (end_of_game(server))
        stop = 0;
}
