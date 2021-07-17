/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** bct
*/

#include "server.h"

/**
* @brief Send an error to the Graphical clients.
*
* @param client Current graphical clients.
* @param array Contains different parts of the command.
*/
static void error_case(client_t *client, char **array)
{
    my_strcat(&client->buffer, "sbp\n");
    free_array(array);
}

/**
* @brief Add a number to the client buffer.
*
* @param client Graphical client.
* @param num Number to transform in string.
*/
static void add_pos(client_t *client, int num)
{
    char *str = my_int_to_char(num);

    my_strcat(&client->buffer, str);
    free(str);
}

/**
* @brief Send all need informations to graphical client.
*
* @param map The current map case.
* @param client The graphical client.
* @param x Column of the current map case.
* @param y Line of the current map case.
*/
static void get_cell(map_t map, client_t *client, int x, int y)
{
    my_strcat(&client->buffer, "bct ");
    add_pos(client, x);
    my_strcat(&client->buffer, " ");
    add_pos(client, y);
    my_strcat(&client->buffer, " ");
    add_pos(client, map.food_number);
    my_strcat(&client->buffer, " ");
    add_pos(client, map.ressources.linemate);
    my_strcat(&client->buffer, " ");
    add_pos(client, map.ressources.deraumere);
    my_strcat(&client->buffer, " ");
    add_pos(client, map.ressources.sibur);
    my_strcat(&client->buffer, " ");
    add_pos(client, map.ressources.mendiane);
    my_strcat(&client->buffer, " ");
    add_pos(client, map.ressources.phiras);
    my_strcat(&client->buffer, " ");
    add_pos(client, map.ressources.thystame);
    my_strcat(&client->buffer, "\n");
}

/**
* @brief Get ressources inside specified map case.
*
* @param client Current graphical client.
* @param server Contains all informations about the current game.
*/
void bct(client_t *client, server_t *server)
{
    char **array = str_to_word_array(client->readbuffer, " ");
    int x = 0;
    int y = 0;

    if (!array || size_array(array) < 3 || is_digit(array[1]) == false || \
is_digit(array[2]) == false)
        return error_case(client, array);
    x = atoi(array[1]);
    y = atoi(array[2]);
    if (x < 0 || y < 0 || x >= server->args.width || y >= server->args.height)
        return error_case(client, array);
    get_cell(server->map[y][x], client, x, y);
    free_array(array);
}
