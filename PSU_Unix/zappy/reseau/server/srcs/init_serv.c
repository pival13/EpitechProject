/*
** EPITECH PROJECT, 2020
** Created by theo on 08/06/2020.
** File description:
** init_serv.c
*/

#include "my.h"

int server_start(game_t game)
{
    struct sockaddr_in sock;

    if ((game.listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Server-socket() error lol!");
        exit(1);
    }
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = INADDR_ANY;
    sock.sin_port = htons(game.port);
    memset(&(sock.sin_zero), '\0', 8);
    if (bind(game.listener, (struct sockaddr *)&sock, sizeof(sock)) == -1)
        exit(84);
    inet_aton(IP, (struct in_addr *)&sock.sin_addr.s_addr);
    if (listen(game.listener, 10) == -1) {
        exit(1);
    }
    return server_loop(&game);
}
