/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "my.h"

int condition_error_gestion(char **av, int a, int check)
{
    if (is_int(av[a])) {
        if (my_strcmp("-n", av[a - 1]) == 0 || \
my_strcmp("-a", av[a - 1]) == 0 || my_strcmp("-dump", av[a - 1]) == 0)
            check = 1;
        else
            check = -1;
    } else {
        if (my_strcmp2(".cor", av[a]) == 0 || \
my_strcmp("-dump", av[a]) == 0 || my_strcmp("-a", av[a]) == 0 || \
my_strcmp("-n", av[a]) == 0)
            check = 1;
        else
            check = -1;
    }
    return (check);
}

int error_gestion(char **av, int ac)
{
    int check = 0;

    for (int a = 1; a != ac; a++) {
        check = condition_error_gestion(av, a, check);
        if (check == -1)
            return (84);
        else
            check = 0;
    }
    return (0);
}

int main(int ac, char **av)
{
    virtualmachine_t *vm = NULL;

    if (error_gestion(av, ac) == 84) {
        my_dprintf(2, "Invalid argument");
        return (84);
    }
    if (ac == 2 && !my_strcmp("-h", av[1]))
        return (h_function());
    create_vm(ac, av, &vm);
    if (!vm || vm->nb_champion < 1)
        return (84);
    virtualmachine(vm);
    free_vm(vm);
    return (0);
}
