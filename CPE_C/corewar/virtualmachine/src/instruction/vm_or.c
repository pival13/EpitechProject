/*
** EPITECH PROJECT, 2019
** vm_or
** File description:
** vm_or
*/

#include "my.h"

void vm_or(op_t op, virtualmachine_t *vm, int i)
{
    unsigned int value1 = 0;
    unsigned int value2 = 0;

    if (check_bin(op, vm, i) == 0) {
        vm->champion[i].pc += find_size_vm(vm->memory, vm->champion[i].pc);
        vm->champion[i].carry = 0;
        return;
    }
    value1 = get_value(vm, i, 1);
    value2 = get_value(vm, i, 2);
    set_value(vm, i, 3, value1 | value2);
    vm->champion[i].carry = 0;
    if ((value1 | value2) == 0)
        vm->champion[i].carry = 1;
    vm->champion[i].pc += find_size_vm(vm->memory, vm->champion[i].pc);
}
