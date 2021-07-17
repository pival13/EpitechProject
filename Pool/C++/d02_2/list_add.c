/*
** EPITECH PROJECT, 2020
** list_add.c
** File description:
** add functions for list
*/

#include "generic_list.h"
#include <stdlib.h>

bool list_add_elem_at_front(list_t *front_ptr, void *elem)
{
    list_t ptr = malloc(sizeof(node_t));

    if (ptr == NULL)
        return false;
    ptr->value = elem;
    ptr->next = *front_ptr;
    *front_ptr = ptr;
    return true;
}

bool list_add_elem_at_back(list_t *front_ptr, void *elem)
{
    list_t list = *front_ptr;
    list_t ptr = malloc(sizeof(node_t));

    if (ptr == NULL)
        return false;
    ptr->value = elem;
    ptr->next = NULL;
    if (list != NULL) {
        while (list->next != NULL)
            list = list->next;
        list->next = ptr;
    } else
        *front_ptr = ptr;
    return true;
}

bool list_add_elem_at_position(list_t *front_ptr, void *elem,
                                        unsigned int position)
{
    list_t list = *front_ptr;
    list_t ptr;

    if (position > list_get_size(list))
        return false;
    if (position == 0)
        return list_add_elem_at_front(front_ptr, elem);
    for (; position != 1; position--)
        list = list->next;
    ptr =  malloc(sizeof(node_t));
    if (ptr == NULL)
        return false;
    ptr->value = elem;
    ptr->next = list->next;
    list->next = ptr;
    return true;
}
