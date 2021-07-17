/*
** EPITECH PROJECT, 2020
** Created by theo on 12/05/2020.
** File description:
** graphicals_com.c
*/

#include "rfc.h"

static t_pointeur tab[] = {
    {"msz", &map_size},
    {"bct", &content_tile},
    {"mct", &content_map},
    {"tna", &name_team},
    {"ppo", &p_position},
    {"plv", &p_level},
    {"pin", &p_inventory},
    {"sgt", &time_request},
    {"sst", &time_modification},
    {"pdi", &death},
    {"pgt", &resource_collecting},
    {"pdr", &resource_dropping},
    {"pnw", &connect_player},
    {"pic", &start_incantation},
    {"pie", &end_incantation},
    {"pfk", &egg_laying},
    {"enw", &egg_laying_other},
    {"eht", &graph_egg_hatching},
    {"ebo", &connect_egg},
    {"pna", &all_player},
    {"Longer", &longer},
    {"seg", &end_game_graph},
    {"pex", &explusion},
    {NULL, NULL},
};

char *all_player(__attribute__((unused))char *cmd, game_t *game)
{
    char *rfc = NULL;
    int size;
    player_t *players = game->player;
    teams_t *teams = game->teams;
    char *buffer = NULL;

    for (; players != NULL; players = players->next) {
        rfc = my_malloc(1024);
        for (; teams != NULL; teams = teams->next) {
            if (teams->nbr == players->game->team) break;
        }
        if (teams == NULL) continue;
        size = sprintf(rfc, "pnw %s %d %d %d %d %s\n",
            players->game->uuid, players->game->posX,
            players->game->posY, players->game->orientation,
            players->game->level, teams->name);
        rfc[size] = '\0';
        buffer = my_strcat(buffer, rfc);
    }
    return buffer;
}

char *explusion(char *cmd,
    __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(my_strlen(cmd) + 1);
    int i = 0;

    for (; cmd[i] != '\0'; i++)
        rfc[i] = cmd[i];
    rfc[i] = 0;
    return rfc;
}

char *connect_player(char *cmd, __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(64);
    int i = 0;

    for (; cmd[i] != '\0'; i++)
        rfc[i] = cmd[i];
    rfc[i] = 0;
    return rfc;
}

char *unknow_com(__attribute__((unused))char *cmd,
    __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(5);
    int size;

    size = sprintf(rfc, "suc\n");
    rfc[size] = '\0';
    return rfc;
}

char *commmand_param(__attribute__((unused))char *cmd,
    __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(5);
    int size;
    memset(rfc, 0, 5);
    size = sprintf(rfc, "sbp\n");
    rfc[size] = '\0';
    return rfc;
}

char *graphics_command(game_t *game, char *buffer)
{
    for (int i = 0; tab[i].flags != NULL; i++) {
        if (strncmp(tab[i].flags, buffer, 3) == 0) {
            return tab[i].funct(buffer, game);
        }
    }
    return unknow_com(buffer, game);
}