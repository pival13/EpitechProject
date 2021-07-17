/*
** EPITECH PROJECT, 2019
** ldi
** File description:
** lldi
*/

#include "my.h"

void fill_reg(int *p, virtualmachine_t *vm, unsigned int *reg, unsigned int *nb)
{
    if (get_type(vm->memory[(vm->champion[p[0]].pc + 1) % MEM_SIZE], p[1] + 1\
) == 1)
        reg[p[1]] = get_bytes(vm->champion[p[0]].reg, REG_SIZE * (nb[p[1]] - \
1), REG_SIZE);
    else if (get_type(vm->memory[(vm->champion[p[0]].pc + 1) % MEM_SIZE], p[1\
] + 1) == 3)
        reg[p[1]] = get_bytes(vm->memory, vm->champion[p[0]].pc + \
nb[p[1]], DIR_SIZE);
    else
        reg[p[1]] = nb[p[1]];
}

void vm_ldi(op_t op, virtualmachine_t *vm, int p)
{
    unsigned int nb[2];
    unsigned int reg[2];
    unsigned int value;

    if (check_bin(op, vm, p) == 0) {
        vm->champion[p].carry = 0;
        vm->champion[p].pc += find_size_vm(vm->memory, vm->champion[p].pc);
        return;
    }
    nb[0] = get_bytes(vm->memory, vm->champion[p].pc + 2, IND_SIZE);
    nb[1] = get_bytes(vm->memory, vm->champion[p].pc + 2 + IND_SIZE, IND_SIZE);
    for (int i = 0; i != 2; i++)
        fill_reg((int[2]){p, i}, vm, reg, nb);
    value = get_bytes(vm->memory, vm->champion[p].pc + (short)(reg[0] + \
reg[1]) % IDX_MOD, REG_SIZE);
    set_bytes(vm->champion[p].reg, value, REG_SIZE * get_bytes(vm->memory, \
vm->champion[p].pc + 2 + 2 * IND_SIZE, 1), REG_SIZE);
    vm->champion[p].carry = 1;
    vm->champion[p].pc += find_size_vm(vm->memory, vm->champion[p].pc);
}

void vm_lldi(op_t op, virtualmachine_t *vm, int p)
{
    unsigned int nb[2];
    unsigned int reg[2];
    unsigned int value;

    if (check_bin(op, vm, p) == 0) {
        vm->champion[p].carry = 0;
        vm->champion[p].pc += find_size_vm(vm->memory, vm->champion[p].pc);
        return;
    }
    nb[0] = get_bytes(vm->memory, vm->champion[p].pc + 2, IND_SIZE);
    nb[1] = get_bytes(vm->memory, vm->champion[p].pc + 2 + IND_SIZE, IND_SIZE);
    for (int i = 0; i != 2; i++)
        fill_reg((int[2]){p, i}, vm, reg, nb);
    value = get_bytes(vm->memory, vm->champion[p].pc + reg[0] + reg[1], \
REG_SIZE);
    set_bytes(vm->champion[p].reg, value, REG_SIZE * get_bytes(vm->memory, \
vm->champion[p].pc + 2 + 2 * IND_SIZE, 1), REG_SIZE);
    vm->champion[p].carry = 1;
    vm->champion[p].pc += find_size_vm(vm->memory, vm->champion[p].pc);
}
