/*
** EPITECH PROJECT, 2020
** Created by theo on 16/06/2020.
** File description:
** server_read_graph.c
*/

#include "my.h"

char *server_check_buffer_graphics(graphics_t **client, char *buffer)
{
    char *buf = my_strcat((*client)->buffer, buffer);
    int i = my_strlen(buf) - 1;

    for (; i >= 0; i--) {
        if (buf[i] == '\n') break;
    }
    if (i == 0) return NULL;
    if (i == my_strlen(buf) - 1) {
        my_free((*client)->buffer);
        (*client)->buffer = NULL;
    } else
        (*client)->buffer = strcpy((*client)->buffer, (*client)->buffer + i);
    buf[i] = '\0';
    return buf;
}

game_t *server_deco_graph(game_t *game, graphics_t *mem, char *buffer)
{
    int fd;

    printf("\033[0;32m[SERVER]->disconnect graphiques: %d\n\033[0m", mem->fd);
    FD_CLR(mem->fd, &game->read_fds);
    fd = mem->fd;
    game->graph = remove_graphs(game->graph, mem->fd);
    close(fd);
    my_free(buffer);
    return game;
}

int size_tab(char **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    return i;
}

graphics_t *server_reader_graph(char *buffer, graphics_t *mem)
{
    char **tab = NULL;

    buffer = server_check_buffer_graphics(&mem, buffer);
    if (buffer != NULL) {
        tab = my_tab(buffer, '\n');
        printf("\033[0;33m[GRAPH %d]->%s\n\033[0m", mem->fd, buffer);
        for (int i = 0; tab[i] != NULL; i++)
            mem->pile = add_command(mem->pile, tab[i]);
        free_tab(tab);
    }
    my_free(buffer);
    return mem;
}

game_t *server_read_graphics(game_t *game)
{
    graphics_t *mem = game->graph;
    char *buffer;
    int read_size, k;

    for (graphics_t *tmp; mem != NULL;) {
        k = 0;
        if (FD_ISSET(mem->fd, &game->read_fds)) {
            buffer = my_malloc(1024);
            if ((read_size = read(mem->fd, buffer, 1023)) <= 0) {
                tmp = mem->next;
                game = server_deco_graph(game, mem, buffer);
                k = 1;
                mem = tmp;
            } else {
                buffer[read_size] = 0;
                if (read_size >= 1000) add_command_first(mem->pile, "Longer");
                else
                    mem = server_reader_graph(buffer, mem);
            }
        }
        if (k == 0) mem = mem->next;
    }
    return game;
}