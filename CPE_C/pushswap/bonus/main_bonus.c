/*
** EPITECH PROJECT, 2018
** main_bonus
** File description:
** main of the bonus of my pushswap
*/

#include "pushswap.h"
#include "my.h"

int main(int n, char **arg)
{
    int i = 1;
    int j = 0;
    list_t *list;

    if (n < 2)
        return (84);
    if (arg[1][0] == '-' && arg[1][1] == 'v' && arg[1][2] == '\0') {
        i++;
        j++;
    }
    if (n < i+1)
        return (84);
    for (int k = i; k != n; k++)
        if (my_str_isnum(arg[i]) != 1)
            return (84);
    list = prepare_list(n-i, &arg[i]);
    pushswap(&list, j);
    free_list(list);
    my_putchar('\n');
}
