/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** check_map_limit
*/

#include "server.h"

/**
* @brief Check if current position is out of range in the map.
*
* @param y Current line's position
* @param client Current client.
* @param server Contains all information about the current game.
* @return int
*/
int check_map_y(int y, client_t *client, server_t *server)
{
    int posy = y;
    if (y < 0) {
        posy = server->args.height + y;
        if (posy < 0) {
            return check_map_y(posy, client, server);
        }
    } else if (y >= server->args.height) {
        posy = y - server->args.height;
        if (posy >= server->args.height) {
            return check_map_y(posy, client, server);
        }
    }
    return posy;
}

/**
* @brief Check if current position is out of range in the map.
*
* @param x Current column's position.
* @param client Current client.
* @param server Contains all information about the current game.
* @return ints
*/
int check_map_x(int x, client_t *client, server_t *server)
{
    int posx = x;
    if (x < 0) {
        posx = server->args.width + x;
        if (posx < 0) {
            return check_map_x(posx, client, server);
        }
    } else if (x >= server->args.width) {
        posx = x - server->args.width;
        if (posx >= server->args.width) {
            return check_map_x(posx, client, server);
        }
    }
    return posx;
}

/**
* @brief Set the x pos object.
*
* @param turn Direction.
* @param x Line where is the client.
* @param i Position to look depending of the level.
* @param client Current client.
* @return int
*/
int set_x_pos(int turn, int x, int i, client_t *client)
{
    if (turn == 1) {
        if (client->direc == LEFT) {
            return client->x - i;
        } else if (client->direc == RIGHT) {
            return client->x + i;
        }
    } else if (turn == 2) {
        if (client->direc == UP) {
            return client->x + i;
        } else if (client->direc == DOWN) {
            return client->x - i;
        }
    }
    return x;
}

/**
* @brief Set the y pos object.
*
* @param turn Direction.
* @param y Line where is the client.
* @param i Position to look depending of the level.
* @param client Current client.
* @return int
*/
int set_y_pos(int turn, int y, int i, client_t *client)
{
    if (turn == 1) {
        if (client->direc == UP) {
            return client->y - i;
        } else if (client->direc == DOWN) {
            return client->y + i;
        }
    } else if (turn == 2) {
        if (client->direc == RIGHT) {
            return client->y + i;
        } else if (client->direc == LEFT) {
            return client->y - i;
        }
    }
    return y;
}
