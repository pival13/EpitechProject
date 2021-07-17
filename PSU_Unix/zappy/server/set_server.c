/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** set_server
*/

#include "server.h"

/**
* @brief Accept connection of a new user.
*
* @param server Contains all informations about the current game.
*/
void handle_new_connection(server_t *server)
{
    int new_socket = 0;
    int len = sizeof(server->address);

    if (FD_ISSET(server->master_socket, &(server->readfds))) {
        if ((new_socket = accept(server->master_socket, (struct sockaddr *) \
&server->address, (socklen_t *)&len)) < 0) {
            printf("accept failed\n");
            return;
        }
        add_node_back(&(server->client), new_socket);
    }
}

/**
* @brief Find the biggest fd of client link list.
*
* @param all The client link list.
* @param master_socket Fd of the server.
* @return int
*/
static int max_fd_all(client_t *all, int master_socket)
{
    int fd = master_socket;

    for (client_t *tmp = all; tmp; tmp = tmp->next)
        if (tmp->socket > fd)
            fd = tmp->socket;
    return fd + 1;
}

/**
* @brief Loop until a client send a message.
*
* @param server Contains all informations about the current game.
* @return int
*/
int handle_select(server_t *server)
{
    if (server->time.tv_usec == 0) {
        server->time.tv_sec = 0;
        server->time.tv_usec = (1.f / server->args.freq) * 1000000;
    }
    if (select(max_fd_all(server->client, server->master_socket), \
&server->readfds, &server->writefds, NULL, &server->time) < 0) {
        stop = 0;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
* @brief Create fd write/read list with the fd of each clients
* which are inside the client link list.
*
* @param server Contains all informations about the current game.
*/
void handle_fd(server_t *server)
{
    client_t *tmp = server->client;

    FD_ZERO(&(server->readfds));
    FD_ZERO(&(server->writefds));
    FD_SET(server->master_socket, &(server->readfds));

    for (; tmp != NULL; tmp = tmp->next) {
        FD_SET(tmp->socket, &(server->readfds));
        if (tmp->buffer != NULL)
            FD_SET(tmp->socket, &(server->writefds));
    }
}
