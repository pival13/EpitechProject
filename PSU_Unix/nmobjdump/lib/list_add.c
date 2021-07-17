/*
** EPITECH PROJECT, 2020
** list_add.c
** File description:
** add functions for list
*/

#include "generic_list.h"

bool list_push_front(list_t *front_ptr, void *elem)
{
    list_t ptr = malloc(sizeof(node_t));

    if (ptr == NULL)
        return false;
    ptr->value = elem;
    ptr->next = *front_ptr;
    *front_ptr = ptr;
    return true;
}

bool list_push_back(list_t *front_ptr, void *elem)
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

bool list_push(list_t *front_ptr, void *elem, size_t position)
{
    list_t list = *front_ptr;
    list_t ptr;

    if (position > list_size(list))
        return false;
    if (position == 0)
        return list_push_front(front_ptr, elem);
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
