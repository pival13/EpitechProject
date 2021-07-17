/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** incantation
*/

#include "server.h"

static void bci(server_t *server, client_t *client, client_t *cli, size_t size)
{
    int k = 1;

    for (size_t i = 1; i < size; ++i) {
        if (i > (size_t)server->map[client->y][client->x].nb_clients)
            return;
        cli = found_client_with_fd(server, server->map\
[client->y][client->x].socket_list[i - 1]);
        if (!cli || cli->is_incantating || cli->lvl != client->lvl) {
            ++size;
            continue;
        }
        my_strcat(&cli->buffer, "Elevation underway\n");
        cli->lvl == client->lvl ? cli->is_incantating = true : 0;
        client->incantation[k] = cli->socket;
        if (cli->lvl == client->lvl && cli->command_array[0] == NULL)
            cli->command_array[0] = strdup("FakeIncantation");
        cli->cooldown += 300.f / server->args.freq;
        ++k;
    }
}

/**
* @brief Send elevation underway to all the client whom fulfill the
* prerequisite
*
* @param server Contains all informations about the current game.
* @param y Current map's line.
* @param x Current map's column;
* @param level Current level of player.
*/
static void send_incantation_client_first_part(server_t *server, \
client_t *client)
{
    client_t *cli = NULL;
    json_t *json = json_get_with_key(server->json, "elevationPath");
    size_t size = 0;

    if (!json)
        return;
    size = json_get_number(json_get_with_key(json_get_at_index\
(json, client->lvl - 1), "player"));
    client->is_incantating = true;
    my_strcat(&client->buffer, "Elevation underway\n");
    client->incantation[0] = client->socket;
    bci(server, client, cli, size);
}

/**
* @brief Check if client fulfill the prerequisite to make an incantation.
*
* @param server Contains all informations about the current game.
* @param client Current client.
*/
void send_incantation_first_part(server_t *server, client_t *client)
{
    if (!verify_all_key(server, client)) {
        send_client(client, "ko\n");
        return remove_first_command(server, client, server->args.freq);
    }
    if (!prerequisite(server, client, json_get_with_key(server->json, \
"elevationPath"), client->lvl - 1)) {
        send_client(client, "ko\n");
        return remove_first_command(server, client, server->args.freq);
    } else {
        send_incantation_client_first_part(server, client);
        pic(server, server->map[client->y][client->x], client->lvl, client);
    }
}
