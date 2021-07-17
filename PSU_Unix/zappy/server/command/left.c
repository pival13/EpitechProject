/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** left
*/

#include "server.h"

/**
* @brief Turns the player to the left.
*
* @param client Player who execute the command.
*/
void left(client_t *client, __attribute__((unused)) server_t *server)
{
    char *str = NULL;

    switch (client->direc) {
    case LEFT:
        client->direc = DOWN;
        break;
    case UP:
        client->direc = LEFT;
        break;
    case RIGHT:
        client->direc = UP;
        break;
    default:
        client->direc = RIGHT;
        break;
    }
    my_strcat(&client->buffer, "ok\n");
    ppo_answer(client, &str);
    my_strcat(&str, "\n");
    send_to_all_graphic(server->client, str);
    free(str);
}
