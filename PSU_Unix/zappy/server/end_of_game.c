/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** end_of_game
*/

#include "server.h"

static bool add_buffer_end_of_game(client_t *cli, server_t *server)
{
    char *str = NULL;
    char *won = NULL;

    if (cli == NULL)
        return false;
    str = strdup("seg ");
    my_strcat(&str, cli->team_name);
    my_strcat(&str, "\n");
    my_strcat(&won, cli->team_name);
    my_strcat(&won, " WON\n");
    send_to_all_graphic(server->client, str);
    for (client_t *cli = server->client; cli; cli = cli->next)
        if (cli->graphic == false && cli->is_connect == true)
            send_client(cli, won);
    free(str);
    free(won);
    return true;
}

/**
 * @brief Determine if the game has been won by someone.
 *
 * @param server Contains all informations about the game.
 * @param client Current game.
 */
bool end_of_game(server_t *server)
{
    client_t *cli = NULL;
    int go = 0;

    for (int i = 0; server->args.name[i]; ++i) {
        for (cli = server->client; cli && go != 6; cli = cli->next) {
            (cli->lvl == 8 && my_strcmp(server->args.name[i], \
cli->team_name) == 0) ? ++go : 0;
        }
        if (go == 6)
            break;
        go = 0;
    }
    return add_buffer_end_of_game(cli, server);
}
