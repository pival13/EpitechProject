/*
** EPITECH PROJECT, 2020
** Created by theo on 20/06/2020.
** File description:
** graph_times.c
*/

#include "rfc.h"

char *time_request(__attribute__((unused))char *cmd, game_t *game)
{
    char *rfc = my_malloc(64);
    int size;

    memset(rfc, 0, 64);
    size = sprintf(rfc, "sgt %f\n", (float)((float)1 / (float)game->freq));
    rfc[size] = '\0';
    return rfc;
}

char *time_modification(char *cmd, game_t *game)
{
    char *rfc = my_malloc(64);
    int new_time = my_getnbr(cmd + 4);
    int size;
    memset(rfc, 0, 64);
    size = sprintf(rfc, "sst %d\n", new_time);

    if (new_time > 0)
        game->freq = new_time;
    else {
        my_free(rfc);
        return commmand_param(cmd, game);
    }
    rfc[size] = '\0';
    return rfc;
}

char *longer(__attribute__((unused))char *cmd,
    __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(28);

    rfc = strcpy(rfc, "WARNING: too longer buffer\n");
    rfc[27] = '\0';
    return rfc;
}

char *end_game_graph(char *cmd, __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(64);
    int i = 0;

    for (; cmd[i] != '\0'; i++)
        rfc[i] = cmd[i];
    rfc[i] = 0;
    return rfc;
}