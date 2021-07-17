/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** move
*/

#include "server.h"

/**
* @brief Move the player to the left
*
* @param server Contains all informations about the current game.
* @param client Player who execute the command.
*/
void move_left(server_t *server, client_t *client)
{
    delete_client(&server->map[client->y][client->x], client->socket);
    if (client->x - 1 < 0)
        client->x = server->args.width - 1;
    else
        client->x -= 1;
    add_client(&server->map[client->y][client->x], client->socket);
}

/**
* @brief Move the player to the right.
*
* @param server Contains all informations about the current game.
* @param client Player who execute the command.
*/
void move_right(server_t *server, client_t *client)
{
    delete_client(&server->map[client->y][client->x], client->socket);
    if (client->x + 1 > server->args.width - 1)
        client->x = 0;
    else
        client->x += 1;
    add_client(&server->map[client->y][client->x], client->socket);
}

/**
* @brief Move the player up
*
* @param server Contains all informations about the current game.
* @param client Player who execute the command.
*/
void move_up(server_t *server, client_t *client)
{
    delete_client(&server->map[client->y][client->x], client->socket);
    if (client->y - 1 < 0)
        client->y = server->args.height - 1;
    else
        client->y -= 1;
    add_client(&server->map[client->y][client->x], client->socket);
}

/**
* @brief Move the player down
*
* @param server Contains all informations about the current game.
* @param client Player who execute the current command.
*/
void move_down(server_t *server, client_t *client)
{
    delete_client(&server->map[client->y][client->x], client->socket);
    if (client->y + 1 > server->args.height - 1)
        client->y = 0;
    else
        client->y += 1;
    add_client(&server->map[client->y][client->x], client->socket);
}
