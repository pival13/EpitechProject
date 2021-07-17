/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send
*/

#include "server.h"

/**
* @brief Send informations to graphical clients.
*
* @param server Contains all informations about the game.
* @param client Player who is sending a broadcast.
* @param arg Message to send given by the player.
*/
void send_broadcast_to_graphic(server_t *server, client_t *client, char *arg)
{
    char *str = NULL;
    char *number = my_int_to_char(client->id);

    my_strcat(&str, "pbc ");
    my_strcat(&str, number);
    my_strcat(&str, " ");
    my_strcat(&str, arg);
    my_strcat(&str, "\n");
    send_to_all_graphic(server->client, str);
    free(str);
    free(number);
}

/**
* @brief Get the text to send.
*
* @param command Command given by the player.
* @return char *
*/
char *get_text_to_broadcast(char *command)
{
    char *arg = malloc(sizeof(char) * strlen(command));
    size_t index = 0;
    bool begin = false;

    memset(arg, 0, strlen(command));
    for (size_t i = 0; command[i] != 0; ++i) {
        if (command[i] == ' ' && begin == false) {
            begin = true;
        } else if (begin == true) {
            arg[index] = command[i];
            ++index;
        }
    }
    return arg;
}

/**
* @brief Set the write receiver's buffer with the message.
*
* @param client Player who will receive the message.
* @param message Message to send.
* @param fd Fd of current player.
*/
void send_broadcast(client_t *client, char *message, int fd)
{
    if (client->socket == fd) {
        my_strcat(&client->buffer, "ok\n");
    } else {
        my_strcat(&client->buffer, message);
    }
}

/**
* @brief Create the message to send.
*
* @param arg Sended text given by the user.
* @param dir Direction on which the player receive the message.
* @return char *
*/
char *create_message(char *arg, char *dir)
{
    char *message = NULL;

    my_strcat(&message, "message ");
    my_strcat(&message, dir);
    my_strcat(&message, ", ");
    my_strcat(&message, arg);
    my_strcat(&message, "\n");
    return message;
}
