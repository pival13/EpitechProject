/*
** EPITECH PROJECT, 2020
** lists
** File description:
** generic functions for lists
*/

#include "generic_list.h"
#include <stdio.h>

size_t list_size(list_t list)
{
    size_t size = 0;

    while (list != NULL) {
        size++;
        list = list->next;
    }
    return size;
}

bool list_empty(list_t list)
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
        list_pop_front(front_ptr);
}

void list_sort(list_t front_ptr, value_comparator_t comp)
{
    list_t ptr = front_ptr;
    void *tmp;

    while (ptr != NULL && ptr->next != NULL) {
        if (comp(ptr->value, ptr->next->value) > 0) {
            tmp = ptr->value;
            ptr->value = ptr->next->value;
            ptr->next->value = tmp;
            ptr = front_ptr;
        } else
            ptr = ptr->next;
    }
}