/*
** EPITECH PROJECT, 2020
** Created by theo on 19/06/2020.
** File description:
** ia_command_inv.c
*/

#include "rfc_ia.h"

static char *resource[7] = {
    "food\0",
    "linemate\0",
    "deraumere\0",
    "sibur\0",
    "mendiane\0",
    "phiras\0",
    "thystame\0"
};

static double angle_cast[8][2] = {
    {337.5, 22.5},
    {22.5, 57.5},
    {57.5, 112.5},
    {122.5, 157.5},
    {157.5, 202.5},
    {202.5, 247.5},
    {247.5, 292.5},
    {292.5, 337.5},
};

player_t *inventory(player_t *client, __attribute__((unused))game_t **game)
{
    int check = 0;
    char *buf = NULL;

    client->response = my_charcat(client->response, '[');
    for (int i = 0; i < 7; i++) {
        if (client->game->inventory[i] != 0) {
            if (check == 1)
                client->response = my_charcat(client->response, ',');
            check = 1;
            client->response = my_strcat_second(client->response, resource[i]);
            client->response = my_charcat(client->response, ' ');
            buf = malloc(64);
            sprintf(buf, "%d", client->game->inventory[i]);
            client->response = my_strcat(client->response, buf);
        }
    }
    client->response = my_charcat(client->response, ']');
    client->response = my_charcat(client->response, '\n');
    return client;
}

player_t *broadcast_second(player_t *client, player_t *players, map_t *map)
{
    char *buffer;
    int angle;
    int i;
    int size;

    if (players->fd == client->fd || players->fd == -1)
        return players;
    buffer = malloc(1024);
    angle = find_angle(client, players, map);
    for (i = 0; angle > 0 && i < 8; i++) {
        if (angle_cast[i][0] <= angle && angle < angle_cast[i][1]) break;
    }
    i++;
    size = sprintf(buffer, "message %d,%s\n", i, client->pile->command + 9);
    buffer[size] = '\0';
    players->pile = add_command(players->pile, buffer);
    free(buffer);
    return players;
}

player_t *broadcast(player_t *client, game_t **game)
{
    player_t *players = (*game)->player;
    map_t *map = (*game)->map;

    for (int i = 0; players != NULL; players = players->next) {
        players = broadcast_second(client, players, map);
        i++;
    }
    client->response = malloc(4);
    client->response = my_strcpy(client->response, "ok\n");
    return client;
}