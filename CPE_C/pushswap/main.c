/*
** EPITECH PROJECT, 2018
** main_pushswap
** File description:
** main of pushswap
*/

#include "pushswap.h"
#include "my.h"

int main(int n, char **arg)
{
    list_t *list;

    if (n < 2)
        return (84);
    for (int i = 1; i != n; i++)
        if (my_str_isnum(arg[i]) != 1)
            return (84);
    list = prepare_list(n-1, &arg[1]);
    pushswap(&list, 0);
    free_list(list);
    my_putchar('\n');
    return (0);
}
