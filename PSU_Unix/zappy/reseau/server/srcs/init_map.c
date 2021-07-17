/*
** EPITECH PROJECT, 2020
** Created by theo on 08/06/2020.
** File description:
** init_map.c
*/

#include "my.h"

game_t gest_options(game_t game, int ac, char **av)
{
    for (int i = 0, j = 0; i < ac; i++) {
        if (strcmp(av[i], "-n") == 0) {
            for (i++; av[i][0] != '-'; i++, j++)
                game.teams = add_teams(game.teams, av[i], j);
            game.teamnb = j;
        }
        if (strcmp(av[i], "-p") == 0)
            game.port = my_getnbr(av[++i]);
        if (strcmp(av[i], "-f") == 0)
            game.freq = my_getnbr(av[++i]);
        if (strcmp(av[i], "-x") == 0)
            game.map->X = my_getnbr(av[++i]);
        if (strcmp(av[i], "-y") == 0)
            game.map->Y = my_getnbr(av[++i]);
        if (strcmp(av[i], "-c") == 0)
            game.clientNB = my_getnbr(av[++i]);
    }
    game.is_end = false;
    return game;
}

game_t init_value(game_t game)
{
    game.teams = NULL;
    game.freq = 100;
    game.port = 0;
    game.map->X = 0;
    game.map->Y = 0;
    game.clientNB = 0;
    game.player = NULL;
    game.graph = NULL;
    game.client = NULL;
    game.tv.tv_sec = 0;
    return game;
}

int analyse_value(game_t game)
{
    if (game.teams == NULL) {
        printf("Teams not valid");
        return 84;
    }
    if (game.clientNB <= 0) {
        printf("Size team not valid");
        return 84;
    }
    if (game.map->X < 5 || game.map->Y < 5) {
        printf("Size map not valid: Need 5 minimum");
        return 84;
    }
    if (game.port <= 0) {
        printf("Port not valid");
        return 84;
    }
    if (game.freq <= 0) {
        printf("Freq not valid");
        return 84;
    }
    return 0;
}

int init_games(int ac, char **av)
{
    game_t game;

    if (ac < 11) return 84;
    game.map = my_malloc(sizeof(map_t));
    game = init_value(game);
    game = gest_options(game, ac, av);
    game.tv.tv_usec = 1000000 / game.freq;
    if (analyse_value(game) == 84)
        return 84;
    game.teams = init_teams(game.teams, game.clientNB);
    game.map->tiles = init_map(game);
    return server_start(game);
}