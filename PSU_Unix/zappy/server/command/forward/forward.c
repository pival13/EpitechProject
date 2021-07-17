/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** forward
*/

#include "server.h"

/**
* @brief If an error has occured send error.
*
* @param client Current client.
* @param array Contains command which has been split into words.
*/
static void add_pos(char **str, int num)
{
    char *number = my_int_to_char(num);

    my_strcat(str, number);
    free(number);
}

/**
 * @brief Notify that a client moved to all graphic client.
 *
 * @param client Current client.
 * @param str String to fill.
 */
void ppo_answer(client_t *client, char **str)
{
    my_strcat(str, "ppo ");
    add_pos(str, client->id);
    my_strcat(str, " ");
    add_pos(str, client->x);
    my_strcat(str, " ");
    add_pos(str, client->y);
    my_strcat(str, " ");
    switch (client->direc) {
    case UP: return add_pos(str, 1);
    case RIGHT: return add_pos(str, 2);
    case DOWN: return add_pos(str, 3);
    default: return add_pos(str, 4);
    }
}

/**
* @brief Move the client depending on its direction.
*
* @param client Player who execute the command.
* @param server Contains all informations about the current game.
*/
void forward(client_t *client, server_t *server)
{
    char *str = NULL;

    switch (client->direc) {
    case LEFT:
        move_left(server, client);
        break;
    case RIGHT:
        move_right(server, client);
        break;
    case UP:
        move_up(server, client);
        break;
    default:
        move_down(server, client);
        break;
    }
    my_strcat(&client->buffer, "ok\n");
    ppo_answer(client, &str);
    my_strcat(&str, "\n");
    send_to_all_graphic(server->client, str);
    free(str);
}
