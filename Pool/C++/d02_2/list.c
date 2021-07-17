/*
** EPITECH PROJECT, 2020
** lists
** File description:
** generic functions for lists
*/

#include "generic_list.h"
#include <stdlib.h>
#include <stdio.h>

unsigned int list_get_size(list_t list)
{
    unsigned int size = 0;

    while (list != NULL) {
        size++;
        list = list->next;
    }
    return size;
}

bool list_is_empty(list_t list)
{
    return list == NULL;
}

void list_dump(list_t list, value_displayer_t val_disp)
{
    while (list != NULL) {
        val_disp(list->value);
        list = list->next;
    }
}

void list_clear(list_t *front_ptr)
{
    while (*front_ptr != NULL)
        list_del_elem_at_front(front_ptr);
}