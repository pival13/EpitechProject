/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** look
*/

#include "server.h"

/**
* @brief Add the corresponding separator.
* @param client Current client.
*
*/
static void check_char(client_t *client, \
__attribute__((unused))server_t *server)
{
    if (client->buffer[strlen(client->buffer) - 1] != ',' && \
client->buffer[strlen(client->buffer) - 1] != '[' && \
client->buffer[strlen(client->buffer) - 1] != ' ')
        my_strcat(&client->buffer, " ");
}

/**
* @brief Check ressources of the map.
*
* @param x Column's index.
* @param y Line's index.
* @param client Current client.
* @param server Contains all informations about the current game.
*
*/
static void check_map_second(int x, int y, client_t *client, server_t *server)
{
    for (int i = 0; i < server->map[y][x].ressources.linemate; i++)
        i > 0 ? my_strcat(&client->buffer, " linemate") : \
        my_strcat(&client->buffer, "linemate");
    check_char(client, server);
    for (int i = 0; i < server->map[y][x].ressources.mendiane; i++)
        i > 0 ? my_strcat(&client->buffer, " mendiane") : \
        my_strcat(&client->buffer, "mendiane");
    check_char(client, server);
    for (int i = 0; i < server->map[y][x].ressources.phiras; i++)
        i > 0 ? my_strcat(&client->buffer, " phiras") : \
        my_strcat(&client->buffer, "phiras");
    check_char(client, server);
    for (int i = 0; i < server->map[y][x].ressources.sibur; i++)
        i > 0 ? my_strcat(&client->buffer, " sibur") : \
        my_strcat(&client->buffer, "sibur");
    check_char(client, server);
    for (int i = 0; i < server->map[y][x].ressources.thystame; i++)
        i > 0 ? my_strcat(&client->buffer, " thystame") : \
        my_strcat(&client->buffer, "thystame");
}

/**
* @brief Check ressources of the map.
*
* @param x Column's index.
* @param y Line's index.
* @param client Current client.
* @param server Contains all informations about the current game.
*/

static void check_map(int x, int y, client_t *client, server_t *server)
{
    x = check_map_x(x, client, server);
    y = check_map_y(y, client, server);
    for (int i = 0; i < server->map[y][x].nb_clients; i++)
        i > 0 ? my_strcat(&client->buffer, " player") : \
        my_strcat(&client->buffer, "player");
    check_char(client, server);
    for (int i = 0; i < server->map[y][x].food_number; i++)
        i > 0 ? my_strcat(&client->buffer, " food") : \
        my_strcat(&client->buffer, "food");
    check_char(client, server);
    for (int i = 0; i < server->map[y][x].ressources.deraumere; i++)
        i > 0 ? my_strcat(&client->buffer, " deraumere") : \
        my_strcat(&client->buffer, "deraumere");
    check_char(client, server);
    check_map_second(x, y, client, server);
}

/**
* @brief Check ressources of the map.
*
* @param x Column's index.
* @param y Line's index.
* @param client Current client.
* @param server Contains all informations about the current game.
*/

static void look_around(client_t *client, server_t *server)
{
    int posy = 0;
    int posx = 0;
    for (int i = 0; i <= client->lvl; i++) {
        posy = set_y_pos(1, client->y, i, client);
        posx = set_x_pos(1, client->x, i, client);
        for (int j = -i; j <= i; j++) {
            posx = set_x_pos(2, posx, j, client);
            posy = set_y_pos(2, posy, j, client);
            check_map(posx, posy, client, server);
            (i == client->lvl && j == i) ? (0) : \
            (client->buffer[strlen(client->buffer) - 1] == ' ') ? \
client->buffer[strlen(client->buffer) - 1] = ',' : \
my_strcat(&client->buffer, ",");
        }
    }
}

/**
* @brief Look the surrounding of the player.
*
* @param client Current client.
* @param server Contains all informations about the current games.
*/
void look(client_t *client, server_t *server)
{
    my_strcat(&client->buffer, "[");
    look_around(client, server);
    if (client->buffer[strlen(client->buffer) - 1] == ' ') {
        client->buffer[strlen(client->buffer) - 1] = ']';
        my_strcat(&client->buffer, "\n");
    } else
        my_strcat(&client->buffer, "]\n");
}
