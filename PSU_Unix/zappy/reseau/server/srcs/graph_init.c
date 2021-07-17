/*
** EPITECH PROJECT, 2020
** Created by theo on 11/06/2020.
** File description:
** graph_init.c
*/

#include "rfc.h"

char *map_size(__attribute__((unused))char *cmd, game_t *game)
{
    char *rfc = my_malloc(64);

    memset(rfc, 0, 64);
    sprintf(rfc, "msz %d %d\n", game->map->X, game->map->Y);
    return rfc;
}

char *content_tile(char *cmd, game_t *game)
{
    char *rfc = my_malloc(64);
    char **tabl = my_tab(cmd, ' ');
    int X = my_getnbr(tabl[1]);
    int Y = my_getnbr(tabl[2]);
    int size;

    memset(rfc, 0, 64);
    if (X >= game->map->X || X < 0 || Y >= game->map->Y || Y < 0) {
        my_free(rfc);
        return commmand_param(cmd, game);
    }
    size = sprintf(rfc, "bct %d %d %d %d %d %d %d %d %d\n",
        X, Y, game->map->tiles[X][Y].resource[0],
        game->map->tiles[X][Y].resource[1],
        game->map->tiles[X][Y].resource[2],
        game->map->tiles[X][Y].resource[3],
        game->map->tiles[X][Y].resource[4],
        game->map->tiles[X][Y].resource[5],
        game->map->tiles[X][Y].resource[6]);
    rfc[size] = '\0';
    return rfc;
}

char *content_map(__attribute__((unused))char *cmd, game_t *game)
{
    char *buf = NULL;
    char rfc[129];
    int size = 0;
    int tmp;

    for (int Y = 0; Y < game->map->Y; Y++) {
        for (int X = 0; X < game->map->X; X++) {
            tmp = snprintf(rfc, 128, "bct %d %d %d %d %d %d %d %d %d\n", X, Y,
                game->map->tiles[Y][X].resource[0],
                game->map->tiles[Y][X].resource[1],
                game->map->tiles[Y][X].resource[2],
                game->map->tiles[Y][X].resource[3],
                game->map->tiles[Y][X].resource[4],
                game->map->tiles[Y][X].resource[5],
                game->map->tiles[Y][X].resource[6]);
            buf = realloc(buf, size + tmp + 1);
            strcpy(buf + size, rfc);
            size += tmp;
        }
    }
    return buf;
}

char *name_team(__attribute__((unused))char *cmd, game_t *game)
{
    teams_t *teams = game->teams;
    char *rfc = my_malloc(64);
    char *response = NULL;
    int size = 0;

    memset(rfc, 0, 64);
    for (; teams != NULL; teams = teams->next) {
        memset(rfc, 0, 64);
        size = sprintf(rfc, "tna %s\n", teams->name);
        rfc[size] = '\0';
        response = my_strcat(response, rfc);
    }
    return response;
}