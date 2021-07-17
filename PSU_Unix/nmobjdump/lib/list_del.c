/*
** EPITECH PROJECT, 2020
** list_del
** File description:
** delete functions for lists
*/

#include "generic_list.h"

bool list_pop_front(list_t *front_ptr)
{
    list_t ptr;

    if (*front_ptr == NULL)
        return false;
    ptr = (*front_ptr)->next;
    free(*front_ptr);
    *front_ptr = ptr;
    return true;
}

bool list_pop_back(list_t *front_ptr)
{
    list_t list = *front_ptr;

    if (list == NULL)
        return false;
    if (list->next == NULL) {
        free(list);
        *front_ptr = NULL;
    } else {
        while (list->next->next != NULL)
            list = list->next;
        free(list->next);
        list->next = NULL;
    }
    return true;
}

bool list_pop(list_t *front_ptr, size_t position)
{
    list_t list = *front_ptr;
    list_t ptr;

    if (list == NULL || position >= list_size(list))
        return false;
    if (position == 0)
        list_pop_front(front_ptr);
    else {
        for (; position > 1; position--)
            list = list->next;
        ptr = list->next->next;
        free(list->next);
        list->next = ptr;
    }
    return true;
}

bool list_del_node(list_t *front_ptr, node_t *node_ptr)
{
    list_t list = *front_ptr;

    if (*front_ptr == NULL || node_ptr == NULL)
        return false;
    if (*front_ptr == node_ptr)
        list_pop_front(front_ptr);
    else {
        while (list->next != NULL && list->next != node_ptr)
            list = list->next;
        if (list->next == NULL)
            return false;
        list->next = node_ptr->next;
        free(node_ptr);
    }
    return true;
}