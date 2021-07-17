/*
** EPITECH PROJECT, 2019
** create_vm
** File description:
** create the struct vm
*/

#include "my.h"

void find_nb_champ(char **av, virtualmachine_t *vm, int max)
{
    vm->nb_champion = 0;
    for (int ac = 0; ac != max; ac++)
        if (my_strcmp2(".cor", av[ac]) == 0)
            vm->nb_champion++;
}

virtualmachine_t *initialize_vm(virtualmachine_t *vm, int i)
{
    vm->champion[i].n_option = -1;
    vm->champion[i].name = NULL;
    vm->champion[i].nb = 0;
    vm->champion[i].reg = malloc(REG_NUMBER * REG_SIZE);
    if (vm->champion[i].reg == NULL)
        return (NULL);
    for (int a = 0; a != REG_NUMBER * REG_SIZE; a++)
        vm->champion[i].reg[a] = '\0';
    vm->champion[i].pc = 0;
    vm->champion[i].carry = '\0';
    vm->champion[i].live = '\0';
    vm->champion[i].cycle = 0;
    vm->champion[i].a_option = MEM_SIZE / vm->nb_champion * i;
    return (vm);
}

void free_if_error(virtualmachine_t **vm, int ac, char **av)
{
    for (int i = 0; i < (*vm)->nb_champion; i++)
        if (!initialize_vm(*vm, i)) {
            free_registre_error(vm, i);
            return;
        }
    if (create_champ(*vm, ac, av) == 84)
        free_create_champ_error(vm);
}

void create_vm(int ac, char **av, virtualmachine_t **vm)
{
    *vm = malloc(sizeof(virtualmachine_t));
    *vm[0] = (virtualmachine_t){0};
    (*vm)->memory = malloc(sizeof(char) * MEM_SIZE);
    if ((*vm)->memory == NULL) {
        free(*vm);
        return;
    }
    for (int a = 0; a != MEM_SIZE; a++)
        (*vm)->memory[a] = '\0';
    (*vm)->timer = CYCLE_TO_DIE;
    find_nb_champ(av, *vm, ac);
    (*vm)->champion = malloc(sizeof(champ_t) * ((*vm)->nb_champion));
    if ((*vm)->champion == NULL) {
        free_champion_error(vm);
        return;
    }
    free_if_error(vm, ac, av);
}
