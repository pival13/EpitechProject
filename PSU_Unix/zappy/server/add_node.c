/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** add_node
*/

#include "server.h"

/**
* @brief Init ressources of the current node.
*
* @param new_node The node about to be set.
*/
static void init_ressources(client_t *new_node)
{
    new_node->ressources.deraumere = 0;
    new_node->ressources.linemate = 0;
    new_node->ressources.mendiane = 0;
    new_node->ressources.phiras = 0;
    new_node->ressources.sibur = 0;
    new_node->ressources.thystame = 0;
}

/**
* @brief Init current node.
*
* @param new_node The node about to be set.
*/
static void set_array(client_t *new_node)
{
    new_node->food = 10;
    new_node->direc = RIGHT;
    new_node->graphic = false;
    new_node->is_connect = false;
    new_node->pending_command = NULL;
    new_node->egg = false;
    new_node->lvl = 1;
    new_node->x = 0;
    new_node->y = 0;
    new_node->food_time = 0;
    new_node->is_incantating = false;
    for (int i = 0; i < 6; ++i)
        new_node->incantation[i] = 0;
    init_ressources(new_node);
    for (int i = 0; i < 10; ++i)
        new_node->command_array[i] = NULL;
}

/**
* @brief Add first node to the client link list.
*
* @param client The client link list.
* @param new_socket The new client fd.
*/
static void add_first_node(client_t **client, int new_socket)
{
    client_t *new_node = malloc(sizeof(client_t));

    if (new_node == NULL)
        return;
    new_node->next = NULL;
    new_node->socket = new_socket;
    new_node->buffer = strdup("WELCOME\n");
    new_node->is_free = false;
    set_array(new_node);
    new_node->cooldown = 0;
    new_node->id = 0;
    new_node->readbuffer = NULL;
    new_node->team_name = NULL;
    (*client) = new_node;
}

/**
* @brief Add client to the client link list.
*
* @param client The client link list.
* @param new_socket The new client fd.
*/
void add_node_back(client_t **client, int new_socket)
{
    client_t * new_node = NULL;

    if (*client == NULL) {
        add_first_node(client, new_socket);
        return;
    }
    new_node = malloc(sizeof(client_t));
    if (new_node == NULL)
        return;
    client_t *base = (*client);
    for (; base && base->next != NULL; base = base->next);
    new_node->socket = new_socket;
    set_array(new_node);
    new_node->cooldown = 0;
    new_node->buffer = strdup("WELCOME\n");
    new_node->is_free = false;
    new_node->readbuffer = NULL;
    new_node->team_name = NULL;
    new_node->id = 0;
    new_node->next = NULL;
    base->next = new_node;
}
