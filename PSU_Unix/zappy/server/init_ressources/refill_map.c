/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** refill_map
*/

#include "server.h"

/**
 * @brief Refill the map with rocks.
 *
 * @param server Contains all informations about the current game.
 */
static void rock_gestion(server_t *server)
{
    int width = server->args.width;
    int height = server->args.height;
    float pierre = ((float)(height * width) / 5) / 100;
    static int rocks[6] = {0, 0, 0, 0, 0, 0};

    for (float i = 0; i < pierre; i += 1) {
        for (int k = 0; k < 6; ++k)
            ++rocks[k];
        add_linemate(&server->map[rand() % height][rand() % width], \
&rocks[LINEMATE]);
        add_deraumere(&server->map[rand() % height][rand() % width], \
&rocks[DERAUMERE]);
        add_sibur(&server->map[rand() % height][rand() % width], \
&rocks[SIBUR]);
        add_mendiane(&server->map[rand() % height][rand() % width], \
&rocks[MENDIANE]);
        add_phiras(&server->map[rand() % height][rand() % width], \
&rocks[PHIRAS]);
        add_thystame(&server->map[rand() % height][rand() % width], \
&rocks[THYSTAME]);
    }
}

/**
 * @brief Refill all the cells of the map.
 *
 * @param server Contains all the cells of the map.
 */
static void refill_all_cells(server_t *server)
{
    int width = server->args.width;
    int height = server->args.height;
    float food = (height * width * 1.5) / 150;

    for (int i = 0; i < food; ++i) {
        int randomy = rand() % height;
        int randomx = rand() % width;
        if (i + 1 < food && server->map[randomy][randomx].food_number < 5)
            server->map[randomy][randomx].food_number += 1;
        else if (rand() % 10000 < (food - i) * 10000 && \
server->map[randomy][randomx].food_number < 5)
            server->map[randomy][randomx].food_number += 1;
    }
    rock_gestion(server);
}

/**
 * @brief Add ressources on the map during the game.
 *
 * @param server Contains all informations about the current game.
 */
void refill_map(server_t *server)
{
    float passed_time = 0.f;

    if (server->time.tv_usec == 0)
        passed_time = 1.f / server->args.freq;
    server->refill_cooldown -= passed_time;
    if (server->refill_cooldown <= 0) {
        server->refill_cooldown = REFILL / server->args.freq;
        refill_all_cells(server);
    }
}
