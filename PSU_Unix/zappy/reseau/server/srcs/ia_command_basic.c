/*
** EPITECH PROJECT, 2020
** Created by theo on 19/06/2020.
** File description:
** ia_command_basic.c
*/

#include "rfc_ia.h"

player_t *forward_second(player_t *client, game_t **game)
{
    switch (client->game->orientation) {
    case 3:
        client->game->posY++;
        if (client->game->posY == (*game)->map->Y)
            client->game->posY = 0;
        break;
    case 4:
        client->game->posX--;
        if (client->game->posX == -1)
            client->game->posX += (*game)->map->X;
        break;
    }
    return client;
}

player_t *forward(player_t *client, game_t **game)
{
    switch (client->game->orientation) {
    case 1:
        client->game->posY--;
        if (client->game->posY == -1)
            client->game->posY += (*game)->map->Y;
        break;
    case 2:
        client->game->posX++;
        if (client->game->posX == (*game)->map->X)
            client->game->posX = 0;
        break;
    default:
        client = forward_second(client, game);
        break;
    }
    client->response = my_malloc(4);
    client->response = my_strcpy(client->response, "ok\n");
    (*game)->graph = graph_command_forward((*game)->graph, client);
    return client;
}

player_t *connect_nbr(player_t *client, game_t **game)
{
    teams_t *teams = (*game)->teams;
    for (; teams != NULL; teams = teams->next) {
        if (teams->nbr == client->game->team) {
            client->response = int_to_char(teams->limit);
        }
    }
    return client;
}

player_t *right(player_t *client, __attribute__((unused))game_t **game)
{
    client->game->orientation =
        ((client->game->orientation + 1) % 5);
    if (client->game->orientation == 0)
        client->game->orientation = 1;
    client->response = my_malloc(4);
    client->response = my_strcpy(client->response, "ok\n");
    (*game)->graph = graph_command_forward((*game)->graph, client);
    return client;
}

player_t *left(player_t *client, __attribute__((unused))game_t **game)
{
    client->game->orientation =
        ((client->game->orientation - 1) % 5);
    if (client->game->orientation == 0)
        client->game->orientation = 4;
    client->response = my_malloc(4);
    client->response = my_strcpy(client->response, "ok\n");
    (*game)->graph = graph_command_forward((*game)->graph, client);
    return client;
}