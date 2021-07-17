/*
** EPITECH PROJECT, 2019
** kill_champ.c
** File description:
** Created by etienne-miltgen,
*/

#include "my.h"

int kill_champ(virtualmachine_t *vm)
{
    for (int i = 0; i < vm->nb_champion; i++) {
        if (vm->champion[i].live == 0)
            vm->champion[i].live = -1;
        else if (vm->champion[i].live == 1)
            vm->champion[i].live = 0;
    }
    return (0);
}

int condition_nb_alive(virtualmachine_t *vm, int i, int nb)
{
    if (vm->champion[i].live > -1) {
        if (nb == 0) {
            nb = vm->champion[i].nb;
        } else if (nb != vm->champion[i].nb)
            return (-100);
    }
    return (nb);
}

int nb_alive(virtualmachine_t *vm)
{
    int nb = 0;

    for (int i = 0; i < vm->nb_champion; i++) {
        nb = condition_nb_alive(vm, i, nb);
        if (nb == -100)
            return (2);
    }
    return (0);
}

void end_corewar(virtualmachine_t *vm)
{
    if (vm->last_live != -1) {
        my_printf("The player %d(%s) has won.\n", vm->champion[vm->last_live]\
.nb, vm->champion[vm->last_live].name);
        return;
    }
    for (int a = 0; a < vm->nb_champion; a++) {
        if (vm->champion[a].live != -1) {
            my_printf("The player %d(%s) has won.\n", \
vm->champion[a].nb, vm->champion[a].name);
            break;
        }
    }
}
