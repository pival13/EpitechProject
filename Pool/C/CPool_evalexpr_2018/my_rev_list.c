/*
** EPITECH PROJECT, 2018
** my_rev_list.c
** File description:
** reverse list
*/

#include <stdio.h>
#include <stdlib.h>
#include "eval_expr.h"

void my_rev_list(struct_eval_expr **begin)
{
    struct_eval_expr *cell = *begin;
    struct_eval_expr *prev_cell = NULL;
    struct_eval_expr *next_cell = NULL;

    prev_cell = NULL;
    while (cell->next != NULL) {
        next_cell = cell->next;
        cell->next = prev_cell;
        prev_cell = cell;
        cell = next_cell;
    }
    cell->next = prev_cell;
    *begin = cell->next;
}
