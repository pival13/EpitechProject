/*
** EPITECH PROJECT, 2019
** vm_sub
** File description:
** vm_sub
*/

#include "my.h"

void vm_sub(op_t op, virtualmachine_t *vm, int i)
{
    unsigned int value1 = 0;
    unsigned int value2 = 0;

    if (check_bin(op, vm, i) == 0) {
        vm->champion[i].carry = 0;
        vm->champion[i].pc += find_size_vm(vm->memory, vm->champion[i].pc);
        return;
    }
    value1 = get_value(vm, i, 1);
    value2 = get_value(vm, i, 2);
    set_value(vm, i, 3, value1 - value2);
    vm->champion[i].carry = 0;
    if (value1 - value2 == 0)
        vm->champion[i].carry = 1;
    vm->champion[i].pc += find_size_vm(vm->memory, vm->champion[i].pc);
}
