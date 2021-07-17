/*
** EPITECH PROJECT, 2020
** list_get
** File description:
** get functions for lists
*/

#include "generic_list.h"

void *list_get_front(list_t list)
{
    if (list == NULL)
        return NULL;
    return list->value;
}

void *list_get_back(list_t list)
{
    if (list == NULL)
        return NULL;
    while (list->next != NULL)
        list = list->next;
    return list->value;
}

void *list_get(list_t list, size_t position)
{
    if (list == NULL || position >= list_size(list))
        return NULL;
    if (position == 0)
        return list_get_front(list);
    for (; position > 0; position--)
        list = list->next;
    return list->value;
}

node_t *list_get_first_node_with_value(list_t list, void *value,
                                        value_comparator_t val_comp)
{
    if (list == NULL || value == NULL)
        return NULL;
    while (list != NULL && val_comp(list->value, value) != 0)
        list = list->next;
    if (list != NULL)
        return list;
    return NULL;
}