/*
** EPITECH PROJECT, 2019
** virtualmachine
** File description:
** the program
*/

#include "my.h"

void vm_live(op_t op, virtualmachine_t *vm, int champ)
{
    unsigned int size = get_bytes(vm->memory, vm->champion[champ].pc + 1, 4);
    int print = 0;

    for (int i = 0; i != vm->nb_champion; i++) {
        if (vm->champion[i].nb == (int)size && vm->champion[i].live != -1 && !\
print) {
            my_printf("The player %d(%s) is alive.\n", size, vm->champion[i].n\
ame);
            print = 1;
        }
        if (vm->champion[i].nb == (int)size && vm->champion[i].live != -1) {
            vm->champion[i].live = 1;
            vm->last_live = i;
        }
    }
    vm->live++;
    vm->champion[champ].pc += 5;
    if (op.mnemonique || champ)
        return;
}
