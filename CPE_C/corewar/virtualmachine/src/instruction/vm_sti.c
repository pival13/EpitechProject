/*
** EPITECH PROJECT, 2019
** vm_sti
** File description:
** vm_sti
*/

#include "my.h"

void fill_nb(virtualmachine_t *vm, int p, unsigned int nb[3])
{
    nb[0] = get_bytes(vm->memory, vm->champion[p].pc + 2, 1);
    if (get_type(vm->memory[(vm->champion[p].pc + 1) % MEM_SIZE], 2) == 1) {
        nb[1] = get_bytes(vm->memory, vm->champion[p].pc + 3, 1);
        if (get_type(vm->memory[(vm->champion[p].pc + 1) % MEM_SIZE], 3) == 1)
            nb[2] = get_bytes(vm->memory, vm->champion[p].pc + 4, 1);
        else
            nb[2] = get_bytes(vm->memory, vm->champion[p].pc + 4, IND_SIZE);
    } else {
        nb[1] = get_bytes(vm->memory, vm->champion[p].pc + 3, IND_SIZE);
        if (get_type(vm->memory[(vm->champion[p].pc + 1) % MEM_SIZE], 3) == 1)
            nb[2] = get_bytes(vm->memory, vm->champion[p].pc + 3 + \
IND_SIZE, 1);
        else
            nb[2] = get_bytes(vm->memory, vm->champion[p].pc + 3 + IND_SIZE, \
IND_SIZE);
    }
    return;
}

int condition_sti(op_t op, virtualmachine_t *vm, int p, unsigned int nb[3])
{
    if (check_bin(op, vm, p) == 0) {
        vm->champion[p].pc += find_size_vm(vm->memory, vm->champion[p].pc);
        return (84);
    }
    fill_nb(vm, p, nb);
    return (0);
}

void vm_sti(op_t op, virtualmachine_t *vm, int p)
{
    unsigned int nb[3];
    unsigned int reg[3];

    if (condition_sti(op, vm, p, nb) == 84)
        return;
    for (int i = 0; i != 3; i++) {
        if (get_type(vm->memory[(vm->champion[p].pc + 1) % MEM_SIZE], i + 1) =\
= 1)
            reg[i] = get_bytes(vm->champion[p].reg, REG_SIZE * (nb[i]-1), \
REG_SIZE);
        else if (get_type(vm->memory[(vm->champion[p].pc + 1) % MEM_SIZE], i \
+ 1) == 3)
            reg[i] = get_bytes(vm->memory, vm->champion[p].pc + \
(short)nb[i] % IDX_MOD, IND_SIZE);
        else
            reg[i] = nb[i];
    }
    set_bytes(vm->memory, reg[0], vm->champion[p].pc + (short)(reg[1] + \
reg[2]) % IDX_MOD, REG_SIZE);
    vm->champion[p].pc += find_size_vm(vm->memory, vm->champion[p].pc);
}
