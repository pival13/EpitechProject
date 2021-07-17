/*
** EPITECH PROJECT, 2018
** pushswap
** File description:
** Sort a big list of number
*/

#include "pushswap.h"
#include "my.h"
#include <stdlib.h>

list_t *prepare_list(int n, char **num)
{
    list_t *list = NULL;
    list_t *ptr = NULL;
    list_t *mem = NULL;

    for (int i = 0; i != n; i++) {
        do
            list = malloc(sizeof(list_t));
        while (list == NULL);
        (i == 0) ? (mem = list) : mem;
        list->nb = my_getnbr(num[i]);
        list->next = ptr;
        list->prev = ptr;
        ptr = list;
    }
    mem->prev = list;
    mem = list;
    my_rev_list(&list);
    mem->next = list;
    return (list);
}

void free_list(list_t *list)
{
    list_t *mem;

    while (list->next != list) {
        mem = list->next;
        list->next = list->next->next;
        free(mem);
    }
    free(list);
}

int begin_pushswap(list_t **list, int opt)
{
    if (check_list(*list) == 0)
        return (0);
    rotate(list);
    my_putstr("ra");
    if (opt == 1) {
        my_putstr("\nlist a:\t");
        print(list);
        my_putstr("\nlist b:\t\n\n");
    }
    if (check_list(*list) == 0)
        return (0);
    return (1);
}

void put_smallest_first(list_t **list, list_t **list_b, list_t *small, int opt)
{
    list_t *mem = *list;
    int i = 0;
    int j = 0;

    while (mem != small) {
        mem = mem->next;
        i++;
    }
    j = find_size(*list) - i;
    if (i < j)
        for (; i != 0; i--)
            ra(list, list_b, opt);
    else
        for (; j != 0; j--)
            rra(list, list_b, opt);
}

void pushswap(list_t **list, int opt)
{
    list_t *mem = NULL;
    list_t *list_b = NULL;

    if (begin_pushswap(list, opt) == 0)
        return;
    while ((*list)->next != (*list)) {
        mem = find_smallest_nb(*list);
        put_smallest_first(list, &list_b, mem, opt);
        if (check_list(*list) == 0)
            break;
        pb(list, &list_b, opt);
    }
    while (list_b != NULL)
        pa(list, &list_b, opt);
}
