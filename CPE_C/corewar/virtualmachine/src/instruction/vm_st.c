/*
** EPITECH PROJECT, 2019
** vm_st
** File description:
** vm_st
*/

#include "my.h"

void vm_st(op_t op, virtualmachine_t *vm, int i)
{
    unsigned int value = 0;

    if (check_bin(op, vm, i) == 0) {
        vm->champion[i].pc += find_size_vm(vm->memory, vm->champion[i].pc);
        return;
    }
    value = get_value(vm, i, 1);
    set_value(vm, i, 2, value);
    vm->champion[i].pc += find_size_vm(vm->memory, vm->champion[i].pc);
}
