/*
** EPITECH PROJECT, 2020
** doublelist_del
** File description:
** delete elements of a double list
*/

#include "double_list.h"
#include <stdlib.h>
#include <stdbool.h>

bool double_list_del_elem_at_front(double_list_t *front_ptr)
{
    double_list_t ptr;

    if (*front_ptr == NULL)
        return false;
    ptr = (*front_ptr)->next;
    free(*front_ptr);
    *front_ptr = ptr;
    return true;
}

bool double_list_del_elem_at_back(double_list_t *front_ptr)
{
    double_list_t list = *front_ptr;

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

bool double_list_del_elem_at_position(double_list_t *front_ptr,
                                        unsigned int position)
{
    double_list_t list = *front_ptr;
    double_list_t ptr;

    if (list == NULL || position >= double_list_get_size(list))
        return false;
    if (position == 0)
        double_list_del_elem_at_front(front_ptr);
    else {
        for (; position > 1; position--)
            list = list->next;
        ptr = list->next->next;
        free(list->next);
        list->next = ptr;
    }
    return true;
}
