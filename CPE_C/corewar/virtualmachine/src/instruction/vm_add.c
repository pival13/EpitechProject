/*
** EPITECH PROJECT, 2019
** vm_add
** File description:
** vm_add
*/

#include "my.h"

void vm_add(op_t op, virtualmachine_t *vm, int champ)
{
    unsigned int value1 = 0;
    unsigned int value2 = 0;

    if (check_bin(op, vm, champ) == 0) {
        vm->champion[champ].carry = 0;
        vm->champion[champ].pc += find_size_vm(vm->memory, \
vm->champion[champ].pc);
        return;
    }
    value1 = get_value(vm, champ, 1);
    value2 = get_value(vm, champ, 2);
    set_value(vm, champ, 3, value1 + value2);
    vm->champion[champ].carry = 0;
    if (value1 + value2 == 0)
        vm->champion[champ].carry = 1;
    vm->champion[champ].pc += find_size_vm(vm->memory, vm->champion[champ].pc);
    return;
}
