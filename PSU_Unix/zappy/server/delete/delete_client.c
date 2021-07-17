/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** delete_client
*/

#include "server.h"

/**
 * @brief Create a new fd's array.
 *
 * @param node Given map node.
 * @param fd Fd's client.
 * @return int *New fd client array.
 */
static int *delete_array(map_t *node, int fd)
{
    int *tmp_array = malloc(sizeof(int) * (node->nb_clients - 1));
    int index = 0;

    for (int i = 0; i < node->nb_clients; ++i) {
        if (node->socket_list[i] != fd) {
            tmp_array[index] = node->socket_list[i];
            ++index;
        }
    }
    return tmp_array;
}

/**
* @brief Delete a client from the given map cell.
*
* @param node Given map node.
* @param fd Client fd.
*/
void delete_client(map_t *node, int fd)
{
    int *tmp_array = NULL;

    if (node->nb_clients <= 0) {
        node->socket_list = NULL;
        node->nb_clients = 0;
        return;
    }
    if (node->nb_clients - 1 > 0) {
        tmp_array = delete_array(node, fd);
        free(node->socket_list);
        node->socket_list = tmp_array;
        node->nb_clients -= 1;
    } else {
        free(node->socket_list);
        node->socket_list = NULL;
        node->nb_clients = 0;
    }
}
