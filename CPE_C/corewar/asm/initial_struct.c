/*
** EPITECH PROJECT, 2019
** initial
** File description:
** struct
*/

#include "my.h"

void rev_list(asm_t **list)
{
    asm_t *list1 = *list;
    asm_t *nxt = NULL;
    asm_t *previous = NULL;

    if (!list)
        return;
    while (list1->next != NULL) {
        nxt = list1->next;
        list1->next = previous;
        previous = list1;
        list1 = nxt;
    }
    list1->next = previous;
    *list = list1;
}

asm_t *initialize(void)
{
    asm_t *r = malloc(sizeof(asm_t));
    if (r == NULL)
        return (NULL);
    r->other = -1;
    r->label = NULL;
    r->arg = NULL;
    r->param = NULL;
    r->size = 0;
    r->next = NULL;
    return r;
}