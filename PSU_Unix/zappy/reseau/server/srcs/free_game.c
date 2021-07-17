/*
** EPITECH PROJECT, 2020
** Created by theo on 09/06/2020.
** File description:
** my_free_game.c
*/

#include "my.h"

void free_game(game_t *game)
{
    close(game->listener);
    while (game->graph != NULL)
        game->graph = remove_graphs(game->graph, game->graph->fd);
    while (game->player != NULL)
        game->player = remove_player(game->player, game->player->fd);
    for (int i = 0; i < game->map->Y; i++)
        my_free(game->map->tiles[i]);
    my_free(game->map->tiles);
    my_free(game->map);
    while (game->teams != NULL)
        game->teams = remove_teams(game->teams, game->teams->nbr);
}