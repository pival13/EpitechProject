/*
** EPITECH PROJECT, 2020
** Created by theo on 20/05/2020.
** File description:
** look.c
*/

#include "rfc_ia.h"

static char *resource[7] = {"food\0",
    "linemate\0",
    "deraumere\0",
    "sibur\0",
    "mendiane\0",
    "phiras\0",
    "thystame\0"};

char *check_case_second(game_t *game, int pos[2], int check, char *response)
{
    char *temp = NULL;

    for (int k = 0; k < 7; k++) {
        for (int j = 0; j < game->map->tiles[pos[1]][pos[0]].resource[k]; j++) {
            if (check == 1)
                response = my_charcat(response, ' ');
            check = 1;
            temp = my_malloc(15);
            temp = my_strcpy(temp, resource[k]);
            response = my_strcat(response, temp);
        }
    }
    return response;
}

char *check_case(int X, int Y, game_t *game)
{
    player_t *players = game->player;
    char *response = NULL;
    char *temp = NULL;
    int check = 0;
    int pos[2] = {X, Y};

    for (; players != NULL; players = players->next) {
        if (players->game->posX == X &&
            players->game->posY == Y) {
            if (check == 1)
                response = my_charcat(response, ' ');
            check = 1;
            temp = my_malloc(15);
            temp = my_strcpy(temp, "player\0");
            response = my_strcat(response, temp);
        }
    }
    return check_case_second(game, pos, check, response);
}

char *look_switch_case(player_t *client, game_t **game)
{
    switch (client->game->orientation) {
    case 1:
        client->response = my_strcat(client->response,
            look_the_north(client, *game));
        break;
    case 2:
        client->response = my_strcat(client->response,
            look_the_east(client, *game));
        break;
    case 3:
        client->response = my_strcat(client->response,
            look_the_south(client, *game));
        break;
    case 4:
        client->response = my_strcat(client->response,
            look_the_west(client, *game));
        break;
    }
    return client->response;
}

player_t *look(player_t *client, game_t **game)
{
    client->response = NULL;
    client->response = my_charcat(client->response, '[');
    client->response = look_switch_case(client, game);
    client->response = my_charcat(client->response, ']');
    client->response = my_charcat(client->response, '\n');
    return client;
}