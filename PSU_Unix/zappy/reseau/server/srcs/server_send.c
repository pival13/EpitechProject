/*
** EPITECH PROJECT, 2020
** Created by theo on 08/06/2020.
** File description:
** server_send.c
*/

#include "my.h"

char *server_write_error(int write_size, char *error, char *response)
{
    char *second = NULL;

    if (write_size != my_strlen(response)) {
        if (error == NULL) {
            error = my_malloc(my_strlen(response) - write_size);
            error = strcpy(error, response + write_size);
        } else {
            second = my_malloc(my_strlen(response) - write_size);
            second = strcpy(second, response + write_size);
            second = my_strcat(second, error);
            my_free(response);
            return second;
        }
    }
    my_free(response);
    return error;
}

char *server_write_without_error(int fd, char *response)
{
    int write_size;
    char *error = NULL;
    /*char **tab = NULL;

    if (type == 1) {
        tab = my_tab(response, '\n');
        if (size_tab(tab) != 1) {
            my_free(response);
            response = NULL;
            response = my_strcat(response, tab[0]);
            response = my_charcat(response, '\n');
            for (int i = 1; tab[i] != NULL; i++) {
                error = my_strcat(error, tab[i]);
                error = my_charcat(error, '\n');
            }
            my_free(tab);
        } else
            free_tab(tab);
    }*/
    if ((write_size = write(fd, response, my_strlen(response))) == -1) {
        my_free(response);
        close(fd);
    }
    return server_write_error(write_size, error, response);
}

game_t *server_send_ia(game_t *game)
{
    player_t *players = game->player;

    for (; players != NULL && !game->is_end; players = players->next) {
        if (FD_ISSET(players->fd, &game->write_fds)) {
            if (players->error != NULL) {
                players->error = server_write_without_error(players->fd,
                    players->error);
            } else if (players->response != NULL) {
                printf("\033[0;34m[AI RESPONSE %d]->%s\n\033[0m",
                    players->fd, players->response);
                if (my_strcmp(players->response, "death") == 0 ||
                    strncmp(players->response, "WARNING", 7) == 0)
                    players->dead = true;
                players->error = server_write_without_error(players->fd,
                        players->response);
                players->response = NULL;
            }
        }
    }
    return check_dead(game);
}

game_t *server_send_graphics(game_t *game)
{
    graphics_t *graph = game->graph;
    graphics_t *tmp = NULL;

    for (; graph != NULL; graph = graph->next) {
        if (FD_ISSET(graph->fd, &game->write_fds)) {
            if (graph->error != NULL) {
                graph->error = server_write_without_error(graph->fd,
                    graph->error);
            } else if (graph->response != NULL) {
                printf("\033[0;35m[GRAPH RESPONSE %d]->%s\n\033[0m",
                    graph->fd, graph->response);
                if (strncmp(graph->response, "WARNING", 7) == 0)
                    graph->delete = true;
                graph->error = server_write_without_error(graph->fd,
                    graph->response);
                graph->response = NULL;
            }
        }
    }
    for (graph = game->graph; graph != NULL;) {
        if (graph->delete == true && graph->response == NULL) {
            tmp = graph->next;
            printf("\033[0;32m[SERVER]->disconnect graph : %d\n\033[0m", graph->fd);
            game->client = remove_new_client(game->client, graph->fd);
            graph = tmp;
        } else graph = graph->next;
    }
    return game;
}

game_t *server_send_clients(game_t *game)
{
    client_t *client = game->client;
    client_t *tmp = NULL;

    for (; client != NULL && !game->is_end; client = client->next) {
        if (FD_ISSET(client->fd, &game->write_fds)) {
            if (client->error != NULL) {
                client->error = server_write_without_error(client->fd,
                    client->error);
            } else if (client->response != NULL) {
                printf("\033[0;35m[SERVER RESPONSE %d]->%s\n\033[0m",
                    client->fd, client->response);
                server_write_without_error(client->fd, client->response);
                client->response = NULL;
            }
        }
    }
    for (client = game->client; client != NULL;) {
        if (client->delete == true && client->response == NULL) {
            tmp = client->next;
            printf("\033[0;36m[SERVER]->disconnect client tmp: %d\n\033[0m", client->fd);
            game->client = remove_new_client(game->client, client->fd);
            client = tmp;
        } else client = client->next;
    }
    return game;
}