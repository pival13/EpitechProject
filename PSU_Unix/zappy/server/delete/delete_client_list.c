/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** delete_client_list
*/

#include "server.h"

/**
* @brief Delete the first node of the client link list.
*
* @param client The client link list.
*/

static void delete_first_node(client_t **client)
{
    client_t *new_list = (*client);

    new_list = (*client)->next;
    (*client)->buffer != NULL ? free((*client)->buffer) : 0;
    (*client)->team_name != NULL ? free((*client)->team_name) : 0;
    (*client)->readbuffer != NULL ? free((*client)->readbuffer) : 0;
    (*client)->pending_command != NULL ? free((*client)->pending_command) : 0;
    for (int i = 0; i < 10; ++i)
        (*client)->command_array[i] != NULL ? \
free((*client)->command_array[i]) : 0;
    free((*client));
    (*client) = new_list;
}

/**
* @brief Delete a node of the client link list.
*
* @param node A node about to be free.
* @param client The client link list.
*/

static void delete_node(client_t *node, client_t **client)
{
    client_t *new_list = (*client);
    client_t *tmp;

    if (new_list == NULL)
        return;
    if (new_list == node)
        return delete_first_node(client);
    for (; new_list->next != NULL; new_list = new_list->next)
        if (new_list->next == node)
            break;
    for (int i = 0; i < 10; ++i)
        new_list->next->command_array[i] != NULL ? \
free(new_list->next->command_array[i]) : 0;
    new_list->next->team_name != NULL ? free(new_list->next->team_name) : 0;
    new_list->next->buffer != NULL ? free(new_list->next->buffer) : 0;
    new_list->next->readbuffer != NULL ? free(new_list->next->readbuffer) : 0;
    new_list->next->pending_command != NULL ? \
free(new_list->next->pending_command) : 0;
    tmp = new_list->next->next;
    free(node);
    new_list->next = tmp;
}

/**
* @brief Free a node of the client link list.
*
* @param server Contains all informations about the current game.
* @param all If the boolean is set to true, free all node of the
* client link list.
*/

void free_link_list(server_t *server, bool all)
{
    client_t *current = server->client;
    client_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        if (all == true) {
            !current->graphic ? delete_client(&server->map\
[current->y][current->x], current->socket) : 0;
            delete_node(current, &server->client);
        } else if (all == false && current->is_free == true) {
            !current->graphic ? delete_client(&server->map[current->y]\
[current->x], current->socket) : 0;
            delete_node(current, &server->client);
        }
        current = next;
    }
}
