/*
** EPITECH PROJECT, 2018
** my_rev_list.c
** File description:
** Reverse the order of the list
*/

#include <stdlib.h>
#include "pushswap.h"
#include "my.h"

void my_rev_list(list_t **begin)
{
    list_t *cell = *begin;
    list_t *prev_cell = NULL;
    list_t *next_cell = NULL;

    while (cell->next != NULL) {
        next_cell = cell->next;
        cell->next = prev_cell;
        prev_cell = cell;
        cell = next_cell;
    }
    cell->next = prev_cell;
    *begin = cell;
}
