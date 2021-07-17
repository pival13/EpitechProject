/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** server_loop
*/

#include "server.h"

/**
* @brief Either connect or add the command to the client's command array.
*
* @param client Current client.
* @param server Contains all information about the current game.
*/
void launch_command(client_t **client, server_t *server)
{
    if ((*client)->team_name == NULL) {
        welcome_function(client, server);
        if (my_strcmp((*client)->team_name, GRAPHIC_NAME) == 0)
            (*client)->graphic = true;
    } else {
        add_command(client, server);
    }
    free((*client)->readbuffer);
    (*client)->readbuffer = NULL;
}

/**
* @brief Main loop of server.
*
* @param server Contains all informations about the current game.
*/
void server_loop(server_t *server)
{
    handle_fd(server);
    handle_select(server);
    write_all(server);
    free_link_list(server, false);
    if (stop == 0)
        return;
    egg_time_gestion(server);
    exec_each_command(server);
    handle_new_connection(server);
    get_command(server);
    refill_map(server);
}
