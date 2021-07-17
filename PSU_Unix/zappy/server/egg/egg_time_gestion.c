/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** egg_time_gestion
*/

#include "server.h"

/**
* @brief Send informations about the egg to graphical clients.
*
* @param server Contains all informations about the current game.
* @param int Id of the current egg.
*/
void send_egg_hacthing_graphical(server_t *server, unsigned long int id)
{
    char *str = NULL;
    char *number = NULL;

    number = my_int_to_char(id);
    my_strcat(&str, "eht ");
    my_strcat(&str, number);
    my_strcat(&str, "\n");
    send_to_all_graphic(server->client, str);
    free(str);
    free(number);
}

/**
* @brief Handle time hatching egg.
*
* @param server Contains all informations about the current game.
*/
void egg_time_gestion(server_t *server)
{
    float passed_time = 0.f;

    if (server->time.tv_usec == 0)
        passed_time = 1.f / server->args.freq;
    for (egg_t *tmp = server->egg; tmp != NULL; tmp = tmp->next) {
        if (tmp->cooldown > 0)
            tmp->cooldown = tmp->cooldown - passed_time > 0 ? \
tmp->cooldown - passed_time : 0;
        if (tmp->cooldown == 0) {
            tmp->cooldown = -1;
            send_egg_hacthing_graphical(server, tmp->id);
        }
    }
}
