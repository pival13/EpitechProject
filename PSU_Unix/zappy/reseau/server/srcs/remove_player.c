/*
** EPITECH PROJECT, 2020
** Created by theo on 16/06/2020.
** File description:
** remove_player.c
*/

#include "my.h"

player_t *remove_player_second(player_t *mem)
{
    player_t *tmp = tmp = mem->next;

    my_free(mem->buffer);
    my_free(mem->response);
    my_free(mem->error);
    while (mem->pile != NULL)
        mem->pile = remove_command(mem->pile);
    my_free(mem->game->uuid);
    my_free(mem->game->id_inc);
    my_free(mem->game);
    close(mem->fd);
    my_free(mem);
    return tmp;
}

player_t *remove_player_in(player_t *mem)
{
    my_free(mem->next->buffer);
    my_free(mem->next->response);
    my_free(mem->next->error);
    while (mem->next->pile != NULL)
        mem->next->pile = remove_command(mem->next->pile);
    my_free(mem->next->game->uuid);
    my_free(mem->next->game->id_inc);
    my_free(mem->next->game);
    my_free(mem->next);
    mem->next = NULL;
    return mem;
}

player_t *remove_player_other(player_t *mem)
{
    player_t *tmp = mem->next;

    mem->next = tmp->next;
    my_free(tmp->buffer);
    my_free(tmp->response);
    my_free(tmp->error);
    while (tmp->pile != NULL)
        tmp->pile = remove_command(tmp->pile);
    my_free(tmp->game->uuid);
    my_free(tmp->game->id_inc);
    my_free(tmp->game);
    my_free(tmp);
    return mem;
}

player_t *remove_player(player_t *list, int my_fd)
{
    player_t *mem = list;

    if (mem == NULL) return NULL;
    if (mem->fd == my_fd) return remove_player_second(mem);
    for (; mem->next != NULL; mem = mem->next) {
        if (mem->next->fd == my_fd) {
            if (mem->next->next == NULL)
                mem = remove_player_in(mem);
            else
                mem = remove_player_other(mem);
            break;
        }
    }
    close(my_fd);
    return list;
}