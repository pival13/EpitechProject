/*
** EPITECH PROJECT, 2020
** Created by theo on 20/05/2020.
** File description:
** graphs.c
*/

#include "rfc.h"

game_t **new_player_egg(game_t **game, player_t *player)
{
    graphics_t *graphs = (*game)->graph;
    char *rfc = my_malloc(64);

    sprintf(rfc, "ebo %s\n", player->game->uuid);
    for (; graphs != NULL; graphs = graphs->next)
        graphs->pile = add_command(graphs->pile, rfc);
    my_free(rfc);
    return game;
}

game_t **new_player(game_t **game, player_t *player)
{
    teams_t *teams = (*game)->teams;
    graphics_t *graphs = (*game)->graph;
    char *rfc = my_malloc(256);
    int size;

    for (; teams != NULL; teams = teams->next) {
        if (teams->nbr == player->game->team)
            break;
    }
    if (teams == NULL)
        return NULL;
    size = sprintf(rfc, "pnw %s %d %d %d %d %s\n", player->game->uuid,
        player->game->posX, player->game->posY,
        player->game->orientation, player->game->level,
        teams->name);
    rfc[size] = '\0';
    for (; graphs != NULL; graphs = graphs->next)
        graphs->pile = add_command(graphs->pile, rfc);
    my_free(rfc);
    return game;
}