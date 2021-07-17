/*
** EPITECH PROJECT, 2020
** Created by theo on 20/06/2020.
** File description:
** node_tools.c
*/

#include "rfc_ia.h"

tile_t **init_map_second(game_t game, tile_t **tile)
{
    int element[7];
    int ratio, randi, rando;

    if (game.map->Y > game.map->X) ratio = game.map->Y;
    else ratio = game.map->X;
    element[0] = game.clientNB * game.teamnb * ratio * 5;
    element[1] = game.clientNB * game.teamnb * ratio * 5;
    element[2] = game.clientNB * game.teamnb * ratio * 5;
    element[3] = game.clientNB * game.teamnb * ratio * 5;
    element[4] = game.clientNB * game.teamnb * ratio * 5;
    element[5] = game.clientNB * game.teamnb * ratio * 5;
    element[6] = game.clientNB * game.teamnb * ratio * 5;
    for (int i = 0; i < 7; i++) {
        for (; element[i] > 0; element[i]--) {
            rando = my_rand() % game.map->Y;
            randi = my_rand() % game.map->X;
            tile[rando][randi].resource[i]++;
        }
    }
    return tile;
}

tile_t **init_map(game_t game)
{
    tile_t **tile = my_malloc(sizeof(tile_t *) * game.map->Y);
    for (int i = 0; i < game.map->Y; i++) {
        tile[i] = my_malloc(sizeof(tile_t) * game.map->X);
        for (int j = 0; j < game.map->X; j++) {
            for (int k = 0; k < 7; k++)
                tile[i][j].resource[k] = 0;
        }
    }
    return init_map_second(game, tile);
}

teams_t *init_teams(teams_t *teams, int clientnb)
{
    teams_t *tmp = teams;

    for (; tmp != NULL; tmp = tmp->next) {
        tmp->limit = clientnb;
    }
    return teams;
}

teams_t *add_teams(teams_t *teams, char *name, int nbr)
{
    teams_t *tmp = my_malloc(sizeof(teams_t));
    teams_t *mem = teams;

    tmp->name = strdup(name);
    tmp->nbr = nbr;
    tmp->next = NULL;
    if (teams == NULL) {
        return tmp;
    } else {
        for (; mem->next != NULL; mem = mem->next);
        mem->next = tmp;
    }
    return teams;
}

graphics_t *add_graphs(graphics_t *graphs, int fd)
{
    graphics_t *tmp = my_malloc(sizeof(graphics_t));
    graphics_t *mem = graphs;

    tmp->fd = fd;
    tmp->pile = NULL;
    tmp->next = NULL;
    tmp->buffer = NULL;
    tmp->response = NULL;
    tmp->delete = false;
    tmp->error = NULL;
    if (graphs == NULL) {
        return tmp;
    } else {
        for (; mem->next != NULL; mem = mem->next);
        mem->next = tmp;
    }
    return graphs;
}