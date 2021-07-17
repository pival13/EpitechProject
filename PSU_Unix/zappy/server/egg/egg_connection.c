/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** egg_connection
*/

#include "server.h"

/**
* @brief Delete the first node of the egg link list.
*
* @param egg_list The egg link list.
*/

static void delete_first_node(egg_t **egg_list)
{
    egg_t *new_list = *egg_list;

    new_list = (*egg_list)->next;
    free((*egg_list)->team_name);
    free((*egg_list));
    (*egg_list) = new_list;
}

/**
* @brief Delete the current node of the egg link list.
*
* @param node Node about to be free.
* @param egg_list The egg link list.
*/

static void delete_node(egg_t *node, egg_t **egg_list)
{
    egg_t *new_list = *egg_list;
    egg_t *tmp;

    if (new_list == NULL)
        return;
    if (new_list == node)
        return delete_first_node(egg_list);
    for (; new_list->next != NULL; new_list = new_list->next)
        if (new_list->next == node)
            break;
    tmp = new_list->next->next;
    free(node->team_name);
    free(node);
    new_list->next = tmp;
}

/**
* @brief Delete the given egg link list's node.
*
* @param egg egg about ot be free.
* @param egg_list The egg link list.
* @param all If the boolean is set to true, delete all the egg link list.
*/

void delete_egg(egg_t *egg, egg_t **egg_list, bool all)
{
    egg_t *current = *egg_list;
    egg_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        if (all == true)
            delete_node(current, egg_list);
        else if (current == egg)
            return delete_node(current, egg_list);
        current = next;
    }
}

/**
* @brief Update the client informations with the egg content.
*
* @param client Client who is loginning.
* @param egg The egg on which the client is loginning to.
*/

static void update_client(client_t **client, egg_t *egg)
{
    (*client)->team_name = strdup(egg->team_name);
    (*client)->id = egg->id;
    (*client)->x = egg->x;
    (*client)->y = egg->y;
    (*client)->egg = true;
}

/**
* @brief Connect the client on an egg if disponible.
*
* @param server Contains all informations about the current game.
* @param client Client who is loginning.
* @return true
* @return false
*/

bool egg_connection(server_t *server, client_t **cli)
{
    for (egg_t *tmp = server->egg; tmp != NULL; tmp = tmp->next) {
        if (is_equal(tmp->team_name, (*cli)->readbuffer) == true && \
tmp->cooldown == -1) {
            update_client(cli, tmp);
            delete_egg(tmp, &server->egg, false);
            add_client(&server->map[(*cli)->y][(*cli)->x], (*cli)->socket);
            return true;
        }
    }
    return false;
}
