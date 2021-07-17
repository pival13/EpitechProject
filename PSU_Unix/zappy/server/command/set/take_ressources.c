/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** take_ressources
*/

#include "server.h"

/**
* @brief Notify all graphical clients about the item that has been dropped
* and who did it.
*
* @param server Contains all informations about the current game.
* @param client Current client.
* @param index Current ressources.
*/
static void send_set_all_graphic(server_t *server, client_t *client, int index)
{
    char *str = NULL;
    char *number = my_int_to_char(client->id);

    my_strcat(&str, "pdr ");
    my_strcat(&str, number);
    my_strcat(&str, " ");
    free(number);
    number = my_int_to_char(index);
    my_strcat(&str, number);
    my_strcat(&str, "\n");
    send_to_all_graphic(server->client, str);
    free(str);
    free(number);
}

/**
* @brief Put a droped object inside a map case.
*
* @param client Client who dropped the object.
* @param server Contains all informations about the current game.
* @param str The name of the droped object
* @return int
*/
static int take_set_ressources_last_n(client_t *client, server_t *server, \
char *str)
{
    if (strcmp("thystame", str) == 0) {
        if (client->ressources.thystame != 0) {
            server->map[client->y][client->x].ressources.thystame += 1;
            client->ressources.thystame -= 1;
            send_set_all_graphic(server, client, 6);
            send_client(client, "ok\n");
        } else
            send_client(client, "ko\n");
        return 0;
    }
    return EXIT_FAILURE;
}

/**
* @brief Put a dropped object inside a map case.
*
* @param client Client who dropped the object.
* @param server Contains all informations about the current game.
* @param str The name of the dropped object
* @return int
*/
static int take_set_ressources_last(client_t *client, server_t *server, \
char *str)
{
    if (strcmp("mendiane", str) == 0) {
        if (client->ressources.mendiane != 0) {
            server->map[client->y][client->x].ressources.mendiane += 1;
            client->ressources.mendiane -= 1;
            send_set_all_graphic(server, client, 4);
            send_client(client, "ok\n");
        } else
            send_client(client, "ko\n");
    } else if (strcmp("phiras", str) == 0) {
        if (client->ressources.phiras != 0) {
            server->map[client->y][client->x].ressources.phiras += 1;
            client->ressources.phiras -= 1;
            send_set_all_graphic(server, client, 5);
            send_client(client, "ok\n");
        } else
            send_client(client, "ko\n");
    } else
        return take_set_ressources_last_n(client, server, str);
    return 0;
}

/**
* @brief Put a dropped object inside a map case.
*
* @param client Client who dropped the object.
* @param server Contains all informations about the current game.
* @param str The name of the dropped object
* @return int
*/
static int take_set_ressources_next(client_t *client, server_t *server, \
char *str)
{
    if (strcmp("deraumere", str) == 0) {
        if (client->ressources.deraumere != 0) {
            server->map[client->y][client->x].ressources.deraumere += 1;
            client->ressources.deraumere -= 1;
            send_set_all_graphic(server, client, 2);
            send_client(client, "ok\n");
        } else
            send_client(client, "ko\n");
    } else if (strcmp("sibur", str) == 0) {
        if (client->ressources.sibur != 0) {
            server->map[client->y][client->x].ressources.sibur += 1;
            client->ressources.sibur -= 1;
            send_set_all_graphic(server, client, 3);
            send_client(client, "ok\n");
        } else
            send_client(client, "ko\n");
    } else
        return take_set_ressources_last(client, server, str);
    return 0;
}

/**
* @brief Put a dropped object inside a map case.
*
* @param client Client who dropped the object.
* @param server Contains all informations about the current game.
* @param str The name of the dropped object
* @return int
*/
int take_set_ressources(client_t *client, server_t *server, char *str)
{
    if (strcmp("food", str) == 0) {
        if (client->food != 0) {
            server->map[client->y][client->x].food_number += 1;
            client->food -= 1;
            send_set_all_graphic(server, client, 0);
            send_client(client, "ok\n");
        } else
            send_client(client, "ko\n");
    } else if (strcmp("linemate", str) == 0) {
        if (client->ressources.linemate) {
            server->map[client->y][client->x].ressources.linemate += 1;
            client->ressources.linemate -= 1;
            send_set_all_graphic(server, client, 1);
            send_client(client, "ok\n");
        } else
            send_client(client, "ko\n");
    }
    else
        return take_set_ressources_next(client, server, str);
    return 0;
}