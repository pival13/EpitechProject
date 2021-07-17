/*
** EPITECH PROJECT, 2019
** vm_aff
** File description:
** vm_aff
*/

#include "my.h"

void vm_aff(op_t op, virtualmachine_t *vm, int i)
{
    unsigned int value = 0;

    if (check_bin(op, vm, i) == 0) {
        vm->champion[i].pc += find_size_vm(vm->memory, vm->champion[i].pc);
        return;
    }
    value = get_value(vm, i, 1) % 256;
    my_printf("%c\n", value);
    vm->champion[i].pc += find_size_vm(vm->memory, vm->champion[i].pc);
}
