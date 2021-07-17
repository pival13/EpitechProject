/*
** EPITECH PROJECT, 2019
** vm_zjmp
** File description:
** vm_zjmp
*/

#include "my.h"

void vm_zjmp(op_t op, virtualmachine_t *vm, int p)
{
    if (!op.mnemonique)
        return;
    if (vm->champion[p].carry != 1) {
        vm->champion[p].pc += find_size_vm(vm->memory, vm->champion[p].pc);
        return;
    }
    vm->champion[p].pc += (short)get_bytes(vm->memory, vm->champion[p].pc \
+ 1, IND_SIZE) % IDX_MOD;
}
