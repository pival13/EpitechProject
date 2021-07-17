/*
** EPITECH PROJECT, 2020
** list_del
** File description:
** delete functions for lists
*/

#include "generic_list.h"
#include <stdlib.h>

bool list_del_elem_at_front(list_t *front_ptr)
{
    list_t ptr;

    if (*front_ptr == NULL)
        return false;
    ptr = (*front_ptr)->next;
    free(*front_ptr);
    *front_ptr = ptr;
    return true;
}

bool list_del_elem_at_back(list_t *front_ptr)
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

bool list_del_elem_at_position(list_t *front_ptr,
                                        unsigned int position)
{
    list_t list = *front_ptr;
    list_t ptr;

    if (list == NULL || position >= list_get_size(list))
        return false;
    if (position == 0)
        list_del_elem_at_front(front_ptr);
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
        list_del_elem_at_front(front_ptr);
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