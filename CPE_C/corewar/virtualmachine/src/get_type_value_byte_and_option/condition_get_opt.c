/*
** EPITECH PROJECT, 2019
** condition_get_opt
** File description:
** check_if_condition_it's_good_for_launch_virtualmachine
*/

#include "my.h"

static int condition_a_option(virtualmachine_t *vm, char **av, int a, int i)
{
    int value = 0;

    if (vm->champion[i].a_option == MEM_SIZE / vm->nb_champion * i) {
        value = check_argument(av, a);
        if (value != -1)
            vm->champion[i].a_option = value;
        else
            return (1);
    }
    else
        return (1);
    return (0);
}

static int condition_n_option(virtualmachine_t *vm, char **av, int a, int i)
{
    int value = 0;

    if (vm->champion[i].n_option == -1) {
        value = check_argument(av, a);
        if (value != -1)
            vm->champion[i].n_option = value;
        else
            return (1);
    }
    else
        return (1);
    return (0);
}

int condition_get_opt(virtualmachine_t *vm, char **av, int a, int i)
{
    if (my_strcmp2("-a", av[a]) == 0 && my_strcmp2("-n", av[a + 1]) == 0)
        return (0);
    if (my_strcmp2("-a", av[a]) == 0)
        if (condition_a_option(vm, av, a, i) == 1)
            return (1);
    if (my_strcmp2("-n", av[a]) == 0)
        if (condition_n_option(vm, av, a, i) == 1)
            return (1);
    return (0);
}
