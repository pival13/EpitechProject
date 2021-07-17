/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** exec_command
*/

#include "server.h"

/**
* @brief Remove the first commmand of the command array.
*
* @param server Contains all informations about the current game.
* @param client Current client.
* @param freq Number of action in one second.
*/
void remove_first_command(server_t *server, client_t *client, int freq)
{
    for (int i = 0; i < 10 && (client)->command_array[i] != NULL; ++i) {
        free((client)->command_array[i]);
        (client)->command_array[i] = NULL;
        if (i + 1 < 10 && (client)->command_array[i + 1])
            (client)->command_array[i] = strdup((client)->\
command_array[i + 1]);
    }
    client->cooldown = 0;
    if (client->command_array[0] != NULL) {
        client->cooldown = command_cooldown(client->command_array[0]) / freq;
        if (strncmp(client->command_array[0], "Fork", 4) == 0)
            send_egg_laying(server, client);
        else if (strncmp(client->command_array[0], "Incantation", 11) == 0)
            send_incantation_first_part(server, client);
    }
}

/**
* @brief Launch the first command of the command array.
*
* @param client Client who launch the command.
* @param server Contains all informations about the current game.
*/
static void launch_server_command(client_t *client, server_t *server)
{
    char **array = str_to_word_array(client->command_array[0], " ");

    for (int i = 0; basic_command[i]; ++i)
        if (strcmp(array[0], basic_command[i]) == 0)
            command_server[i](client, server);
    free_array(array);
}

/**
* @brief Decrease the cooldown of the first command.
*
* @param client Current client.
* @param server Contains all informations about the current game.
*/
static void decrease_user_cooldown(client_t *client, server_t *server)
{
    float tmp = 0;

    if (client->cooldown <= 0)
        return;
    if (server->time.tv_usec == 0)
        tmp = 1.f / server->args.freq;
    client->cooldown -= tmp;
    client->cooldown < 0 ? client->cooldown = 0 : 0;
}

/**
* @brief Launch the first command available of each clients.
*
* @param server Contains all informations about the current game.
*/
void exec_each_command(server_t *server)
{
    for (client_t *tmp = server->client; tmp != NULL; tmp = tmp->next) {
        decrease_user_cooldown(tmp, server);
        life_gestion(server, tmp);
        if (tmp->cooldown == 0 && tmp->command_array && \
tmp->command_array[0] && tmp->is_free == false) {
            launch_server_command(tmp, server);
            remove_first_command(server, tmp, server->args.freq);
        }
    }
}
