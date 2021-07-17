/*
** EPITECH PROJECT, 2020
** Created by theo on 20/06/2020.
** File description:
** gest_node.c
*/

#include "my.h"

client_t *list_add_new_client(client_t *client, int new_fd)
{
    client_t *tmp = my_malloc(sizeof(client_t));
    client_t *mem = client;

    tmp->fd = new_fd;
    tmp->response = my_malloc(9);
    tmp->response = strcpy(tmp->response, "WELCOME\n");
    tmp->buffer = NULL;
    tmp->delete = false;
    tmp->repo = false;
    tmp->error = NULL;
    tmp->next = NULL;
    if (mem == NULL)
        return tmp;
    for (; mem->next != NULL; mem = mem->next);
    mem->next = tmp;
    return client;
}

game_t *server_add_new_client(game_t *game, int listener)
{
    int new_fd;

    if (FD_ISSET(listener, &game->read_fds)) {
        new_fd = accept(listener, NULL, NULL);
        if (new_fd == -1) return game;
        game->client = list_add_new_client(game->client, new_fd);
        printf("\033[0;32m[SERVER]->new client: %d\n\033[0m", new_fd);
    }
    return game;
}

client_t *remove_new_client(client_t *list, int new_fd)
{
    client_t *mem = list;
    client_t *tmp = NULL;

    if (mem == NULL) return NULL;
    if (mem->fd == new_fd) {
        tmp = mem->next;
        my_free(mem->buffer);
        my_free(mem->response);
        my_free(mem->repo);
        my_free(mem);
        return tmp;
    }
    for (; mem->next != NULL; mem = mem->next) {
        if (mem->next->fd == new_fd) {
            if (mem->next->next == NULL) {
                my_free(mem->next->buffer);
                my_free(mem->next->response);
                my_free(mem->next->repo);
                my_free(mem->next);
                mem->next = NULL;
            } else {
                tmp = mem->next;
                mem->next = tmp->next;
                my_free(tmp->buffer);
                my_free(tmp->response);
                my_free(tmp->repo);
                my_free(tmp);
            }
            break;
        }
    }
    return list;
}

game_t *server_read_clients(game_t *game)
{
    client_t *mem = game->client;
    int read_size, k, fd;

    for (client_t *tmp; mem != NULL && !game->is_end; ) {
        k = 0;
        if (FD_ISSET(mem->fd, &game->read_fds)) {
            mem->buffer = my_malloc(1024);
            if ((read_size = read(mem->fd, mem->buffer, 1023)) <= 0) {
                printf("\033[0;32m[SERVER]->disconnect client: %d\n\033[0m", mem->fd);
                tmp = mem->next;
                fd = mem->fd;
                game->client = remove_new_client(game->client, mem->fd);
                close(fd);
                k = 1;
                mem = tmp;
            } else {
                mem->buffer[read_size] = 0;
                printf("\033[0;32m[SERVER]->%s\n\033[0m", mem->buffer);
                if (mem->response != NULL) {
                    mem->repo = my_strcat(mem->repo, mem->buffer);
                    mem->buffer = NULL;
                } else {
                    if (strcmp(mem->buffer, "GRAPHIC") == 0) {
                        game->graph = add_graphs(game->graph, mem->fd);
                        mem->delete = true;
                    } else
                        game = create_ia(&game, &mem);
                }
                my_free(mem->buffer);
                mem->buffer = NULL;
            }
        }
        if (k == 0)
            mem = mem->next;
    }
    return game;
}