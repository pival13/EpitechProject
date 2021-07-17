/*
** EPITECH PROJECT, 2020
** doublelist.c
** File description:
** double list
*/

#include "double_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

unsigned int double_list_get_size(double_list_t list)
{
    unsigned int size = 0;

    while (list != NULL) {
        size++;
        list = list->next;
    }
    return size;
}

bool double_list_is_empty(double_list_t list)
{
    return list == NULL;
}

void double_list_dump(double_list_t list)
{
    while (list != NULL) {
        printf("%f\n", list->value);
        list = list->next;
    }
}
