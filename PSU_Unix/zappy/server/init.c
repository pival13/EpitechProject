/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** init
*/

#include "server.h"

/**
 * @brief Create a server's socket
 *
 * @param server Contains all informations about the current game.
 * @return int
 */
static int create_socket(server_t *server)
{
    int enable = 1;

    server->master_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (setsockopt(server->master_socket, SOL_SOCKET, SO_REUSEADDR, &enable, \
sizeof(int)) < 0)
        perror("setsockopt");
    if (server->master_socket == -1) {
        printf("Failed to create TCP socket\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
* @brief Init the current server's settings.
*
* @param server Contains all informations about the current game.
* @return int
*/
int init_server(server_t *server)
{
    if (create_socket(server) == EXIT_FAILURE)
        return EXIT_FAILURE;
    bzero(&(server->address), sizeof(server->address));
    (server->address).sin_family = AF_INET;
    (server->address).sin_port = htons(server->args.port);
    (server->address).sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server->master_socket, (struct sockaddr *)\
&(server->address), sizeof(server->address)) == -1) {
        printf("Bind failed\n");
        return 84;
    }
    if (listen(server->master_socket, 1024) != 0) {
        printf("Listen failed\n");
        return 84;
    }
    return EXIT_SUCCESS;
}
