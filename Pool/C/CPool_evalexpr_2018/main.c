/*
** EPITECH PROJECT, 2018
** main of eval_expr
** File description:
** main
*/

#include "my.h"
#include "eval_expr.h"

char *convert_base(char const *, char const *, char const *);

int  main(int ac , char **av)
{
    if (ac == 2) {
		my_putstr(eval_expr(av[1], "0123456789"));
        my_putchar('\n');
        return  (0);
    }
    return  (84);
}
