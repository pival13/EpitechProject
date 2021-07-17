/*
** EPITECH PROJECT, 2019
** virtualmachine
** File description:
** the program
*/

#include "my.h"

void cycle_case(virtualmachine_t *vm, int p)
{
    if (vm->champion[p].cycle == 0) {
        vm->champion[p].cycle = 1;
        vm->champion[p].pc++;
    }
}

int execute_function(int *tab, virtualmachine_t *vm, \
void (*funct[16])(op_t, virtualmachine_t *, int), op_t *op)
{
    if (vm->memory[(MEM_SIZE + vm->champion[tab[1]].pc) % MEM_SIZE] == \
op[tab[0]].code) {
        (*funct[tab[0]])(op[tab[0]], vm, tab[1]);
        tab[0] = 15;
    }
    return (tab[0]);
}

void execute(virtualmachine_t *vm, int p)
{
    op_t *op = op_tab;
    void (*funct[16])(op_t, virtualmachine_t *, int) = {vm_live, vm_ld, vm_st\
, vm_add, vm_sub, vm_and, vm_or, vm_xor, vm_zjmp, vm_ldi, vm_sti, vm_fork\
, vm_lld, vm_lldi, vm_lfork, vm_aff};

    if (vm->champion[p].cycle == 0)
        for (int i = 0; i != 16; i++)
            (vm->memory[(MEM_SIZE + vm->champion[p].pc) % MEM_SIZE] == \
op[i].code) ? (vm->champion[p].cycle = op[i].nbr_cycles) : (0);
    if (vm->champion[p].cycle == 1)
        for (int i = 0; i != 16; i++) {
            i = execute_function((int[2]){i, p}, vm, funct, op);
        }
    cycle_case(vm, p);
    vm->champion[p].cycle--;
}

void virtualmachine(virtualmachine_t *vm)
{
    int cycle_total = 0;

    vm->last_live = -1;
    for (int cycle = 0; nb_alive(vm) > 1; cycle++, cycle_total++) {
        if (cycle_total >= vm->dump && vm->dump != 0)
            return (dump_corewar(vm));
        for (int p = 0; p != vm->nb_champion; p++)
            (vm->champion[p].live >= 0) ? execute(vm, p) : (0);
        if (vm->live >= NBR_LIVE) {
            vm->live -= NBR_LIVE;
            vm->timer -= CYCLE_DELTA;
        }
        if (cycle >= vm->timer) {
            kill_champ(vm);
            cycle = -1;
        }
    }
    end_corewar(vm);
}
