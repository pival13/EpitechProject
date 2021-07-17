/*
** EPITECH PROJECT, 2019
** print_navy.c
** File description:
** funcs to print navy
*/

#include "my.h"
#include "navy.h"

void print_navy2(char **p)
{
    my_printf(" |A B C D E F G H\n-+---------------\n");
    for (int i = 1; i <= 8; i++) {
        my_printf("%d|", i);
        my_printf("%c %c %c %c ", p[i][1], p[i][2], p[i][3], \
p[i][4]);
        my_printf("%c %c %c %c\n", p[i][5], p[i][6], p[i][7], \
p[i][8]);
    }
    my_printf("\n");
}

void print_navy(arrays_t *arrays)
{
    my_printf("my positions:\n");
    print_navy2(arrays->p1);
    my_printf("enemy's positions:\n");
    print_navy2(arrays->p2);
}
