/*
** EPITECH PROJECT, 2019
** check_bin_vm.c
** File description:
** check if the binaire is good
*/

#include "my.h"

int check_bin(op_t op, virtualmachine_t *vm, int champ)
{
    int champbyte = 0;
    int type[4] = {0, T_REG, T_DIR, T_IND};

    for (int i = 0; i < op.nbr_args; i++) {
        champbyte = get_type(vm->memory[(vm->champion[champ].pc + 1) % \
MEM_SIZE], i + 1);
        if ((type[champbyte] & op.type[i]) == 0)
            return (0);
    }
    return (1);
}
