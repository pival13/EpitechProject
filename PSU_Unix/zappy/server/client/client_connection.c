/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** client_connection
*/

#include "server.h"

/**
* @brief Send welcom answer at a new player.
*
* @param client Current client.
* @param server Contains all informations about the current game.
* @param k The number of unused slot in the team.
*/
static void write_answer_welcome(client_t **client, server_t *server, int k)
{
    char *save = NULL;

    if ((*client)->team_name == NULL)
        return;
    k <= 0 ? k = 0 : 0;
    save = my_int_to_char(k);
    (*client)->buffer = strdup(save);
    my_strcat(&(*client)->buffer, "\n");
    free(save);
    save = my_int_to_char(server->args.width);
    my_strcat(&(*client)->buffer, save);
    my_strcat(&(*client)->buffer, " ");
    free(save);
    save = my_int_to_char(server->args.height);
    my_strcat(&(*client)->buffer, save);
    free(save);
    my_strcat(&(*client)->buffer, "\n");
}

/**
 * @brief Update variables of new client.
 *
 * @param cli New client.
 */
static bool update_new_client(server_t *server, client_t **cli)
{
    (*cli)->is_connect = true;
    (*cli)->id = max_in_team();
    if (is_equal((*cli)->readbuffer, GRAPHIC_NAME) == true) {
        write_answer_for_graphic(*cli, server);
        (*cli)->graphic = true;
        return false;
    }
    return true;
}

/**
 * @brief Connect client to the game's sserver
 *
 * @param server Contains all informations about the current game.
 * @param cli Current client.
 * @param k Number of connections which are available yet.
 */
static void connect_client(server_t *server, client_t *cli, int k)
{
    if (egg_connection(server, &cli) == false) {
        if (update_new_client(server, &cli) == false)
            return;
    } else {
        cli->is_connect = true;
        death_egg(server, cli);
    }
    write_answer_welcome(&cli, server, k);
    spawn_client(server, &cli);
    send_new_client_to_graphical(server, cli);
}

/**
* @brief Add team name to the client whom has been accepted.
*
* @param client Current client.
* @param server Contains all informations about the current game.
*/
void welcome_function(client_t **cli, server_t *server)
{
    int k = 0;

    if (team_name_not_found((*cli)->readbuffer, server->args.name) && \
strcmp((*cli)->readbuffer, GRAPHIC_NAME) != 0) {
        (*cli)->is_free = true;
        my_strcat(&(*cli)->buffer, "ko\n");
        return;
    }
    (*cli)->team_name = strdup((*cli)->readbuffer);
    k = hmitt(server, *cli);
    if (k < 0) {
        (*cli)->is_free = true;
        my_strcat(&(*cli)->buffer, "ko\n");
        return;
    }
    connect_client(server, *cli, k);
}
