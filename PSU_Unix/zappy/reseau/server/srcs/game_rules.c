/*
** EPITECH PROJECT, 2020
** Created by theo on 20/06/2020.
** File description:
** game_rules.c
*/

#include "rfc_ia.h"

static int rules[7][7] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

tile_t **change_map(player_t *client, tile_t **tiles)
{
    for (int i = 1; i < 7; i++) {
        tiles[client->game->posY][
            client->game->posX].resource[i] -= rules[
            client->game->level - 1][i];
    }
    return tiles;
}

player_t *game_rules_incantation_end(player_t *client, game_t *game)
{
    player_t *player = game->player;
    int cpt = 0;

    for (; player != NULL; player = player->next) {
        if (my_strcmp(player->game->id_inc,
            client->game->id_inc) == 0 &&
            client->game->posX == player->game->posX &&
            client->game->posY == player->game->posY)
            cpt++;
    }
    if (cpt != rules[client->game->level - 1][0])
        return NULL;
    for (int i = 1; i < 7; i++) {
        if (game->map->tiles[client->game->posY]
            [client->game->posX].resource[i] <
            rules[client->game->level - 1][i]) return NULL;
    }
    game->map->tiles = change_map(client, game->map->tiles);
    return game->player;
}

int *games_rules_incantation_next(player_t *client, game_t *game, int *fds)
{
    for (int i = 1; i < 7; i++) {
        if (game->map->tiles[client->game->posY]
            [client->game->posX].resource[i] <
            rules[client->game->level - 1][i]) {
            my_free(fds);
            return NULL;
        }
    }
    return fds;
}

int *game_rules_incantation_start(player_t *client, game_t *game)
{
    player_t *players = game->player;
    int k = 0;
    int *fds = my_malloc(sizeof(int) * 6);

    for (; k < 6; k++) fds[k] = 0;
    fds[5] = client->fd;
    for (k = 0; players != NULL; players = players->next) {
        if (k == rules[client->game->level - 1][0] - 1) break;
        if (players->game->posX == client->game->posX &&
            players->game->posY == client->game->posY &&
            players->game->level == client->game->level &&
            players->fd != client->fd && players->game->id_inc == NULL) {
            fds[k] = players->fd;
            k++;
        }
    }
    if (k != rules[client->game->level - 1][0] - 1) {
        my_free(fds);
        return NULL;
    }
    return games_rules_incantation_next(client, game, fds);
}