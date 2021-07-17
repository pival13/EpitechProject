/*
** EPITECH PROJECT, 2020
** Created by theo on 16/06/2020.
** File description:
** remove_graph.c
*/

#include "my.h"

graphics_t *remove_graphs_second(graphics_t *mem)
{
    graphics_t *tmp = mem->next;
    my_free(mem->buffer);
    my_free(mem->response);
    my_free(mem->error);
    while (mem->pile != NULL)
        mem->pile = remove_command(mem->pile);
    my_free(mem);
    return tmp;
}

graphics_t *remove_graphs_in(graphics_t *mem)
{
    my_free(mem->next->buffer);
    my_free(mem->next->response);
    my_free(mem->next->error);
    while (mem->next->pile != NULL)
        mem->next->pile = remove_command(mem->next->pile);
    my_free(mem->next);
    mem->next = NULL;
    return mem;
}

graphics_t *remove_graphs_other(graphics_t *mem)
{
    graphics_t *tmp = mem->next;

    mem->next = tmp->next;
    my_free(tmp->buffer);
    my_free(tmp->response);
    my_free(tmp->error);
    while (tmp->pile != NULL)
        tmp->pile = remove_command(tmp->pile);
    my_free(tmp);
    return mem;
}

graphics_t *remove_graphs(graphics_t *list, int my_fd)
{
    graphics_t *mem = list;

    if (mem == NULL) return NULL;
    if (mem->fd == my_fd) return remove_graphs_second(mem);
    for (; mem->next != NULL; mem = mem->next) {
        if (mem->next->fd == my_fd) {
            if (mem->next->next == NULL)
                mem = remove_graphs_in(mem);
            else
                mem = remove_graphs_other(mem);
            break;
        }
    }
    return list;
}