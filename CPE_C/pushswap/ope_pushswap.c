/*
** EPITECH PROJECT, 2018
** ope_pushswap
** File description:
** swap, push and rotate
*/

#include "pushswap.h"
#include <stdlib.h>

void swap(list_t **list)
{
    int mem = (*list)->nb;

    (*list)->nb = (*list)->next->nb;
    (*list)->next->nb = mem;
}

void rotate(list_t **list)
{
    *list = (*list)->next;
}

void rrotate(list_t **list)
{
    *list = (*list)->prev;
}

void push(list_t **lista, list_t **listb)
{
    list_t *mem = *lista;

    if ((*lista)->next != *lista) {
        rotate(lista);
        (*lista)->prev->prev->next = *lista;
        (*lista)->prev = (*lista)->prev->prev;
    } else
        *lista = NULL;
    if (*listb == NULL) {
        (*listb) = mem;
        mem->next = mem;
        mem->prev = mem;
    } else {
        mem->prev = (*listb)->prev;
        (*listb)->prev->next = mem;
        (*listb)->prev = mem;
        mem->next = (*listb);
        rrotate(listb);
    }
}
