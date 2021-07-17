/*
** EPITECH PROJECT, 2018
** mini_ope_pushswap
** File description:
** make ope and note them
*/

#include "pushswap.h"
#include "my.h"
#include <stdlib.h>

void pa(list_t **list, list_t **listb, int opt)
{
    push(listb, list);
    my_putstr(" pa");
    if (opt == 1) {
        my_putstr("\nlist a:\t");
        print(list);
        my_putstr("\nlist b:\t");
        print(listb);
        my_putstr("\n\n");
    }
}

void pb(list_t **list, list_t **listb, int opt)
{
    push(list, listb);
    my_putstr(" pb");
    if (opt == 1) {
        my_putstr("\nlist a:\t");
        print(list);
        my_putstr("\nlist b:\t");
        print(listb);
        my_putstr("\n\n");
    }
}

void ra(list_t **list, list_t **listb, int opt)
{
    rotate(list);
    my_putstr(" ra");
    if (opt == 1) {
        my_putstr("\nlist a:\t");
        print(list);
        my_putstr("\nlist b:\t");
        print(listb);
        my_putstr("\n\n");
    }
}

void rra(list_t **list, list_t **listb, int opt)
{
    rrotate(list);
    my_putstr(" rra");
    if (opt == 1) {
        my_putstr("\nlist a:\t");
        print(list);
        my_putstr("\nlist b:\t");
        print(listb);
        my_putstr("\n\n");
    }
}

void sa(list_t **list, list_t **listb, int opt)
{
    swap(list);
    my_putstr(" sa");
    if (opt == 1) {
        my_putstr("\nlist a:\t");
        print(list);
        my_putstr("\nlist b:\t");
        print(listb);
        my_putstr("\n\n");
    }
}
