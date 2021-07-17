/*
** EPITECH PROJECT, 2020
** doublelist_add
** File description:
** add element in a list of double
*/

#include "double_list.h"
#include <stdlib.h>
#include <stdbool.h>

bool double_list_add_elem_at_front(double_list_t *front_ptr, double elem)
{
    double_list_t ptr = malloc(sizeof(doublelist_node_t));

    if (ptr == NULL)
        return false;
    ptr->value = elem;
    ptr->next = *front_ptr;
    *front_ptr = ptr;
    return true;
}

bool double_list_add_elem_at_back(double_list_t *front_ptr, double elem)
{
    double_list_t list = *front_ptr;
    double_list_t ptr = malloc(sizeof(doublelist_node_t));

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

bool double_list_add_elem_at_position(double_list_t *front_ptr, double elem,
                                        unsigned int position)
{
    double_list_t list = *front_ptr;
    double_list_t ptr;

    if (position > double_list_get_size(list))
        return false;
    if (position == 0)
        return double_list_add_elem_at_front(front_ptr, elem);
    for (; position != 1; position--)
        list = list->next;
    ptr =  malloc(sizeof(doublelist_node_t));
    if (ptr == NULL)
        return false;
    ptr->value = elem;
    ptr->next = list->next;
    list->next = ptr;
    return true;
}
