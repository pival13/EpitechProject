/*
** EPITECH PROJECT, 2020
** Created by theo on 16/06/2020.
** File description:
** server_read_ia.c
*/

#include "my.h"

char *server_check_buffer_ia(player_t **client, char *buffer)
{
    char *buf = my_strcat((*client)->buffer, buffer);
    int i = my_strlen(buf) - 1;

    for (; i >= 0; i--) {
        if (buf[i] == '\n')
            break;
    }
    if (i == 0) return NULL;
    if (i == my_strlen(buf) - 1) {
        my_free((*client)->buffer);
        (*client)->buffer = NULL;
    } else {
        if ((*client)->buffer != NULL)
            (*client)->buffer = strcpy((*client)->buffer,
                (*client)->buffer + i);
    }
    buf[i + 1] = '\0';
    return buf;
}

game_t *server_deco_ia(game_t *game, player_t *mem, char *buffer)
{
    int fd;
    teams_t *teams = game->teams;

    printf("\033[0;32m[SERVER]->disconnect client: %d\n\033[0m", mem->fd);
    game->graph = graph_command_death(game->graph, mem);
    for (; teams != NULL; teams = teams->next) {
        if (teams->nbr == mem->game->team)
            break;
    }
    if (mem->game->is_egg == NOT)
        teams->limit++;
    FD_CLR(mem->fd, &game->read_fds);
    fd = mem->fd;
    game->player = remove_player(game->player, mem->fd);
    close(fd);
    my_free(buffer);
    return game;
}

player_t *server_reader_ia(char *buffer, player_t *mem)
{
    char **tab = NULL;

    printf("\033[0;31m[AI %d]->%s\n\033[0m", mem->fd, buffer);
    buffer = server_check_buffer_ia(&mem, buffer);
    if (buffer != NULL) {
        tab = my_tab(buffer, '\n');
        for (int i = 0; tab[i] != NULL; i++)
            mem->pile = add_command(mem->pile, tab[i]);
        free_tab(tab);
    }
    my_free(buffer);
    return mem;
}

game_t *server_read_ia(game_t *game)
{
    player_t *mem = game->player;
    char *buffer;
    int read_size, k;

    for (player_t *tmp; mem != NULL && !game->is_end;) {
        k = 0;
        if (FD_ISSET(mem->fd, &game->read_fds)) {
            buffer = my_malloc(1024);
            if ((read_size = read(mem->fd, buffer, 1023)) <= 0) {
                tmp = mem->next;
                game = server_deco_ia(game, mem, buffer);
                k = 1;
                mem = tmp;
            } else {
                buffer[read_size] = '\0';
                if (read_size >= 1000) {
                    add_command_first(mem->pile, "Longer");
                    my_free(buffer);
                }
                else mem = server_reader_ia(buffer, mem);
            }
        }
        if (k == 0) mem = mem->next;
    }
    return game;
}