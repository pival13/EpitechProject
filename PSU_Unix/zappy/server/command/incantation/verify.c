/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** verify
*/

#include "server.h"

/**
* @brief Transform an integer to a string and merge it with the first argument
*
* @param str String that need to be concatained with the number.
* @param num int that will be merge with the string.
*/

static void add_pos(char **str, int num)
{
    char *number = my_int_to_char(num);

    my_strcat(str, number);
    free(number);
}

/**
* @brief Notify all graphical clients that an incantation has started
*
* @param server Contains all informations about the current game
* @param map Map's cell
* @param level Current level of the client
* @param client Current client
*/
void pic(server_t *server, map_t map, int level, client_t *client)
{
    client_t *cli = NULL;
    char *str = strdup("pic ");
    add_pos(&str, client->x);
    my_strcat(&str, " ");
    add_pos(&str, client->y);
    my_strcat(&str, " ");

    for (int i = 0; i < map.nb_clients; ++i) {
        cli = found_client_with_fd(server, map.socket_list[i]);
        if (!cli)
            continue;
        if (cli->lvl == level) {
            add_pos(&str, client->id);
            i == map.nb_clients - 1 ? my_strcat(&str, "\n") : \
my_strcat(&str, " ");
        }
    }
    send_to_all_graphic(server->client, str);
    free(str);
}

/**
* @brief Verify if the json file has all the elevation's keys.
*
* @param server Contains all informations about the current game.
* @param client Current client.
* @return true
* @return false
*/
bool verify_all_key(server_t *server, client_t *client)
{
    json_t *json = json_get_with_key(server->json, "elevationPath");

    if (json == NULL || !json_get_with_key(json_get_at_index(json, \
client->lvl - 1), "player") || !json_get_with_key(json_get_at_index(json, \
client->lvl - 1), "linemate") || !json_get_with_key(json_get_at_index\
(json, client->lvl - 1), "deraumere") || !json_get_with_key\
(json_get_at_index(json, client->lvl - 1), "sibur")) {
        return false;
    } else if (!json_get_with_key(json_get_at_index(json, \
client->lvl - 1), "mendiane") || !json_get_with_key(json_get_at_index\
(json, client->lvl - 1), "phiras") || !json_get_with_key\
(json_get_at_index(json, client->lvl - 1), "thystame"))
        return false;
    return true;
}
