/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** init_map
*/

#include "server.h"

/**
* @brief Init each cell of the map.
*
* @param server Contains all informations about the current game.
*/

void init_all_cell_with_ressources(server_t *server)
{
    int width = server->args.width;
    int height = server->args.height;
    int food = height * width * 1.5;
    float pierre = (height * width) / 5;
    void (*add_ressources[])(map_t *map) = {add_linemate_simple, \
add_deraumere_simple, add_sibur_simple, add_mendiane_simple, \
add_phiras_simple, add_thystame_simple};

    for (int i = 0; i < food; ++i)
        server->map[rand() % height][rand() % width].food_number += 1;
    for (int i = 0; i < pierre; ++i)
        add_ressources[rand() % 6](&server->map[rand() % height]\
[rand() % width]);
}

/**
* @brief Init map
*
* @param server Contains all informations about the current game.
*/

void init_map(server_t *server)
{
    server->map = malloc(sizeof(map_t *) * (server->args.height));
    for (int i = 0; i < server->args.height; ++i) {
        server->map[i] = malloc(sizeof(map_t) * (server->args.width));
        for (int j = 0; j < server->args.width; ++j) {
            server->map[i][j].socket_list = NULL;
            server->map[i][j].nb_clients = 0;
            server->map[i][j].food_number = 0;
            server->map[i][j].ressources.linemate = 0;
            server->map[i][j].ressources.deraumere = 0;
            server->map[i][j].ressources.sibur = 0;
            server->map[i][j].ressources.mendiane = 0;
            server->map[i][j].ressources.phiras = 0;
            server->map[i][j].ressources.thystame = 0;
        }
    }
    init_all_cell_with_ressources(server);
}