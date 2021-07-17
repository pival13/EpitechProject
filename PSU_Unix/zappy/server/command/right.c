/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** right
*/

#include "server.h"

/**
* @brief Turns the player to the right.
*
* @param client Player who execute the command.
*/
void right(client_t *client, __attribute__((unused)) server_t *server)
{
    char *str = NULL;

    switch (client->direc) {
    case LEFT:
        client->direc = UP;
        break;
    case UP:
        client->direc = RIGHT;
        break;
    case RIGHT:
        client->direc = DOWN;
        break;
    default:
        client->direc = LEFT;
        break;
    }
    my_strcat(&client->buffer, "ok\n");
    ppo_answer(client, &str);
    my_strcat(&str, "\n");
    send_to_all_graphic(server->client, str);
    free(str);
}
