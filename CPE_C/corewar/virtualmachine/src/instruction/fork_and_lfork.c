/*
** EPITECH PROJECT, 2019
** fork_and_lfork
** File description:
** fork_and_lfork
*/

#include "my.h"

void add_champ(virtualmachine_t *vm, int i)
{
    champ_t *new_tab = malloc(sizeof(champ_t) * (vm->nb_champion + 1));

    for (int a = 0; a != vm->nb_champion; a++)
        new_tab[a] = vm->champion[a];
    new_tab[vm->nb_champion].nb = vm->champion[i].nb;
    new_tab[vm->nb_champion].live = vm->champion[i].live;
    new_tab[vm->nb_champion].cycle = 0;
    new_tab[vm->nb_champion].name = my_strcpy(vm->champion[i].name);
    new_tab[vm->nb_champion].carry = vm->champion[i].carry;
    new_tab[vm->nb_champion].reg = malloc(REG_SIZE * REG_NUMBER);
    for (int a = 0; a != REG_SIZE * REG_NUMBER; a++)
        new_tab[vm->nb_champion].reg[a] = vm->champion[i].reg[a];
    free(vm->champion);
    vm->champion = new_tab;
}

void vm_fork(op_t op, virtualmachine_t *vm, int i)
{
    unsigned int value = 0;

    if (!op.mnemonique)
        return;
    value = get_bytes(vm->memory, vm->memory[(vm->champion[i].pc + 1) % MEM_SI\
ZE], IND_SIZE);
    add_champ(vm, i);
    vm->champion[vm->nb_champion].pc = (vm->champion[i].pc + ((short)value % \
IDX_MOD));
    vm->nb_champion++;
    vm->champion[i].pc += find_size_vm(vm->memory, vm->champion[i].pc);
}

void vm_lfork(op_t op, virtualmachine_t *vm, int i)
{
    unsigned int value = 0;

    if (!op.mnemonique)
        return;
    value = get_bytes(vm->memory, vm->memory[(vm->champion[i].pc + 1) % MEM_SI\
ZE], IND_SIZE);
    add_champ(vm, i);
    vm->champion[vm->nb_champion].pc = (vm->champion[i].pc + value);
    vm->nb_champion++;
    vm->champion[i].pc += find_size_vm(vm->memory, vm->champion[i].pc);
}
