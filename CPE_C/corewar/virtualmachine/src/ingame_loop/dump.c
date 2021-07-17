/*
** EPITECH PROJECT, 2019
** print_type
** File description:
** print the type of element next
*/

#include "my.h"

int dump_condition(virtualmachine_t *vm, char **av, int a)
{
    if (my_strcmp2("-dump", av[a]) == 0) {
        if (vm->dump == 0) {
            vm->dump = check_argument(av, a);
            (vm->dump == -1) ? (vm->dump = 0) : (0);
        } else
            return (1);
    }
    return (0);
}

int dump_option(int ac, char **av, virtualmachine_t *vm)
{
    for (int a = 1; a != ac; a++)
        if (dump_condition(vm, av, a) == 1)
            return (1);
    return (0);
}

void dump_corewar(virtualmachine_t *vm)
{
    int nb = 0;

    for (int i = 0; i != MEM_SIZE; i++) {
        nb = vm->memory[i];
        if (i % 32 == 0)
            my_printf("");
        if (nb == 0)
            my_dprintf(1, "%c%c ", (nb/16 > 9) ? (nb/16 + 'A'-10) : (nb/16 + \
'0'), (nb%16 > 9) ? (nb%16 + 'A'-10) : (nb%16 + '0'));
        else
            my_dprintf(1, "\e[%d;%dm%c%c\e[0m ", (nb+i)%2, (nb+i)%6+31, (nb/16 > 9) ? (nb/16 + 'A'-10) : (nb/16 + '0'), (nb%16 > 9) ? (nb%16 + 'A'-10) : (nb%16 + '0'));
        if (i % 48 == 47)
            my_printf("\n");
    }
    if (vm->last_live != -1) {
        my_printf("The player %d(%s) has won.\n", vm->champion[vm->last_live]\
.nb, vm->champion[vm->last_live].name);
    }
}