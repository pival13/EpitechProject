/*
** EPITECH PROJECT, 2020
** Created by theo on 08/06/2020.
** File description:
** server.c
*/

#include "my.h"

game_t *server_set_reads_fds_next(game_t *game)
{
    graphics_t *graph_mem = game->graph;
    client_t *client_mem = game->client;

    for (; graph_mem != NULL; graph_mem = graph_mem->next) {
        if (graph_mem->fd > game->max) game->max = graph_mem->fd;
        FD_SET(graph_mem->fd, &game->read_fds);
        if (graph_mem->response != NULL)
            FD_SET(graph_mem->fd, &game->write_fds);
    }
    for (; client_mem != NULL; client_mem = client_mem->next) {
        if (client_mem->fd > game->max) game->max = client_mem->fd;
        FD_SET(client_mem->fd, &game->read_fds);
        if (client_mem->response != NULL)
            FD_SET(client_mem->fd, &game->write_fds);
    }
    return game;
}

game_t *server_set_read_fds(game_t *game, int listener)
{
    player_t *mem = game->player;

    FD_ZERO(&game->read_fds);
    FD_ZERO(&game->write_fds);
    game->max = listener;
    FD_SET(listener, &game->read_fds);
    FD_SET(0, &game->read_fds);
    for (; mem != NULL; mem = mem->next) {
        if (mem->fd > game->max) game->max = mem->fd;
        if (mem->fd == -1) continue;
        FD_SET(mem->fd, &game->read_fds);
        if (mem->response != NULL)
            FD_SET(mem->fd, &game->write_fds);
    }
    return server_set_reads_fds_next(game);
}

int gest_stdin(game_t *game)
{
    char *buffer = my_malloc(1024);
    char *command = my_malloc(64);
    graphics_t *temp = game->graph;

    if (FD_ISSET(0, &game->read_fds)) {
        if (read(0, buffer, 1023) != 0) {
            if (strncmp(buffer, "/log", 4) == 0) {
                for (player_t *cli = game->player; cli != NULL; cli = cli->next)
                    printf("\033[0;32m[SERVER]->log: %d\n\033[0m", cli->fd);
            } else if (strncmp(buffer, "/win", 4) == 0) {
                game->is_end = true;
                int size = sprintf(command, "seg aled\n");
                for (command[size] = '\0'; temp != NULL; temp = temp->next)
                    temp->pile = add_command(temp->pile, command);
            } else {
                my_free(buffer);
                my_free(command);
                return 0;
            }
        }
    }
    my_free(buffer);
    my_free(command);
    return 1;
}

int server_loop(game_t *game)
{
    while (true) {
        if (is_end(false)) break;
        game = server_set_read_fds(game, game->listener);
        game = time_gestion(game);
        if (select(game->max + 1, &game->read_fds, &game->write_fds,
            NULL, &game->tv) == -1) break;
        if (gest_stdin(game) == 0) break;
        game = server_add_new_client(game, game->listener);
        game = gest_food(game);
        game = server_read_ia(game);
        game = server_read_graphics(game);
        game = server_read_clients(game);
        game = game_gestion(game);
        game = server_send_ia(game);
        game = server_send_graphics(game);
        game = server_send_clients(game);

    }
    free_game(game);
    return 0;
}