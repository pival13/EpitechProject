/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** eject
*/

#include "server.h"

/**
* @brief Send informations to graphical clients
*
* @param server Contains all information about the current game.
* @param id Id of the curent player.
*/
static void send_eject_to_graphic(server_t *server, int id)
{
    char *str = NULL;
    char *number = my_int_to_char(id);

    my_strcat(&str, "pex ");
    my_strcat(&str, number);
    my_strcat(&str, "\n");
    send_to_all_graphic(server->client, str);
    free(str);
    free(number);
}

/**
* @brief Get the new player position
*
* @param client Player who execute the command.
* @param width Width of the map.
* @param height Height of the map.
* @return int *
*/
static int *get_new_player_pos(client_t *client, int width, int height)
{
    int *array = malloc(sizeof(int) * 2);

    switch (client->direc) {
    case UP:
        array[1] = client->x;
        array[0] = client->y - 1 < 0 ? height - 1 : client->y - 1;
        break;
    case RIGHT:
        array[1] = client->x + 1 > width - 1 ? 0 : client->x + 1;
        array[0] = client->y;
        break;
    case DOWN:
        array[1] = client->x;
        array[0] = client->y + 1 > height - 1 ? 0 : client->y + 1;
        break;
    default:
        array[1] = client->x - 1 < 0 ? width - 1 : client->x - 1;
        array[0] = client->y;
        break;
    }
    return array;
}

/**
* @brief Eject the player from the current map case.
*
*/
static void eject_players(map_t *old_node, map_t *new_node, \
client_t **client, int new_pos[2])
{
    delete_client(old_node, (*client)->socket);
    add_client(new_node, (*client)->socket);
    (*client)->x = new_pos[1];
    (*client)->y = new_pos[0];
}

/**
* @brief Return the fd of the ejected Player.
* @param node The node's cell which contain players.
* @param client_list Contains all client of the current list.
* @param socket Fd of the current client.
* @return client_t *
*/
static client_t *found_player(map_t node, client_t *client_list, \
int socket)
{
    int fd = -1;

    for (int i = 0; i < node.nb_clients; ++i) {
        if (node.socket_list[i] != socket) {
            fd = node.socket_list[i];
            break;
        }
    }
    for (client_t *tmp = client_list; tmp != NULL; tmp = tmp->next)
        if (tmp->socket == fd)
            return tmp;
    return NULL;
}

/**
* @brief Eject everyone else except you.
*
* @param client Player who execute the command.
* @param server Server contains all informations about the current game.
*/
void eject(client_t *cli, server_t *ser)
{
    int *new_pos = NULL;
    client_t *tmp = NULL;

    if (ser->map[cli->y][cli->x].nb_clients <= 1)
        return my_strcat(&cli->buffer, "ko\n");
    new_pos = get_new_player_pos(cli, ser->args.width, ser->args.height);
    for (int i = 0; i < ser->map[cli->y][cli->x].nb_clients; ++i) {
        tmp = found_player(ser->map[cli->y][cli->x], ser->client, cli->socket);
        if (tmp == NULL || tmp->id == cli->id)
            continue;
        eject_players(&ser->map[cli->y][cli->x], \
&ser->map[new_pos[0]][new_pos[1]], &tmp, new_pos);
        send_eject_to_graphic(ser, tmp->id);
        if (cli->x != tmp->x || cli->y != tmp->y)
            send_eject_bc(tmp, (dir_bc(tmp->direc, cli->direc)));
        else
            send_eject_bc(tmp, 0);
    }
    free(new_pos);
    my_strcat(&cli->buffer, "ok\n");
}
