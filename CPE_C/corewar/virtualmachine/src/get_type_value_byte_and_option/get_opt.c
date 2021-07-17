/*
** EPITECH PROJECT, 2019
** get_opt
** File description:
** return the value of the option if present
*/

#include "my.h"

int check_argument(char **av, int a)
{
    if ((my_strcmp2("-n", av[a]) == 0 || my_strcmp2("-dump", av[a]) == 0)\
&& av[a + 1] == NULL)
        return (-1);
    if (my_strcmp2("-a", av[a]) == 0 && \
(my_strcmp2(".cor", av[a + 1]) == 0 || my_strcmp2("-n", av[a + 1]) == 0))
        return (0);
    for (int b = 0; av[a + 1][b] != '\0'; b++) {
        if (av[a + 1][b] < 48 || av[a + 1][b] > 57)
            return (-1);
    }
    return (my_getnbr(av[a + 1]));
}

static int bad_case_condition(char **av, int a)
{
    if ((my_strcmp2("-a", av[a]) == 0 || my_strcmp2("-n", av[a]) == 0) \
&& av[a + 1] == NULL)
        return (1);
    if (my_strcmp2("-n", av[a]) == 0 && my_strcmp2("-a", av[a + 1]) == 0)
        return (1);
    return (0);
}

int get_opt(int ac, char **av, virtualmachine_t *vm)
{
    int i = 0;

    if (dump_option(ac, av, vm) == 1)
        return (84);
    for (int a = 1; a != ac; a++) {
        if (bad_case_condition(av, a) == 1)
            return (84);
        if (condition_get_opt(vm, av, a, i) == 1)
            return (84);
        if (my_strcmp2(".cor", av[a]) == 0) {
            vm->champion[i].name = (unsigned char *)\
(my_strcpy_not_unsigned(av[a]));
            i++;
        }
    }
    return (0);
}
