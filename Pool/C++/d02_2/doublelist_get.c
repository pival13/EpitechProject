/*
** EPITECH PROJECT, 2020
** doublelist_get
** File description:
** get functions for double list
*/

#include "double_list.h"
#include <stdlib.h>
#include <stdbool.h>

double   double_list_get_elem_at_front(double_list_t list)
{
    if (list == NULL)
        return 0;
    return list->value;
}

double   double_list_get_elem_at_back(double_list_t list)
{
    if (list == NULL)
        return 0;
    while (list->next != NULL)
        list = list->next;
    return list->value;
}

double   double_list_get_elem_at_position(double_list_t list,
                                        unsigned int position)
{
    if (list == NULL || position >= double_list_get_size(list))
        return 0;
    if (position == 0)
        return double_list_get_elem_at_front(list);
    for (; position > 0; position--)
        list = list->next;
    return list->value;
}

doublelist_node_t  *double_list_get_first_node_with_value(double_list_t list,
                                                        double value)
{
    if (list == NULL)
        return NULL;
    while (list != NULL && list->value != value)
        list = list->next;
    if (list != NULL)
        return list;
    return NULL;
}