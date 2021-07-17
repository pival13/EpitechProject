/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mct
*/

#include "server.h"

/**
* @brief Get all rescources of the map.
*
* @param client Client who launched the command.
* @param server Contains all informations about the current game.
*/
void mct(client_t *client, server_t *server)
{
    char *s = NULL;
    size_t width = server->args.width;
    size_t height = server->args.height;

    for (size_t y = 0; y < height; ++y)
        for (size_t x = 0; x < width; ++x) {
            s = malloc(sizeof(char) * (193 * (width * height) + 1));
            memset(s, 0, (193 * (width * height) + 1));
            sprintf(s + strlen(s), "bct %ld %ld %d %d %d %d %d %d %d\n", \
x, y, server->map[y][x].food_number, server->map[y][x].ressources.linemate, \
server->map[y][x].ressources.deraumere, server->map[y][x].ressources.sibur, \
server->map[y][x].ressources.mendiane, server->map[y][x].ressources.phiras, \
server->map[y][x].ressources.thystame);
            send_client(client, s);
            free(s);
        }
}
