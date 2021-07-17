/*
** EPITECH PROJECT, 2018
** other_funct
** File description:
** contain some useful function for my_pushswap
*/

#include "pushswap.h"
#include "my.h"
#include <stdlib.h>

list_t *find_smallest_nb(list_t *list)
{
    list_t *mem = list;
    list_t *smallest = list;

    while (list->next != mem) {
        if (list->next->nb < smallest->nb)
            smallest = list->next;
        list = list->next;
    }
    return (smallest);
}

int find_size(list_t *list)
{
    int size = 1;
    list_t *mem = list;

    while (list->next != mem) {
        size++;
        list = list->next;
    }
    return (size);
}

void print(list_t **list)
{
    list_t *mem = *list;

    if (*list != NULL && (*list)->next != *list) {
        do {
            my_put_nbr(mem->nb);
            my_putchar('\t');
            mem = mem->next;
        }
        while (mem->next != *list);
        my_put_nbr(mem->nb);
    } else if (*list == NULL)
        return;
    else
        my_put_nbr(mem->nb);
}

int check_list(list_t *list)
{
    list_t *mem = list;

    for (; list->next != mem && list->nb <= list->next->nb; list = list->next);
    if (list->next == mem)
        return (0);
    return (1);
}
