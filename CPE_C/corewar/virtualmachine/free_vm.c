/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "my.h"

void free_champion_error(virtualmachine_t **vm)
{
    free((*vm)->memory);
    free((*vm));
    vm = NULL;
}

void free_registre_error(virtualmachine_t **vm, int i)
{
    free((*vm)->memory);
    for (int a = 0; a != i - 1; a++) {
        free((*vm)->champion[a].name);
        free((*vm)->champion[a].reg);
    }
    free((*vm)->champion);
    free((*vm));
    vm = NULL;
}

void free_create_champ_error(virtualmachine_t **vm)
{
    free((*vm)->memory);
    for (int a = 0; a != (*vm)->nb_champion; a++) {
        free((*vm)->champion[a].name);
        free((*vm)->champion[a].reg);
    }
    free((*vm)->champion);
    free((*vm));
    (*vm) = NULL;
}

void free_vm(virtualmachine_t *vm)
{
    if (vm != NULL && vm->nb_champion != 0) {
        for (int i = 0; i != vm->nb_champion; i++) {
            free(vm->champion[i].reg);
            free(vm->champion[i].name);
        }
        free(vm->champion);
        free(vm->memory);
    }
    free(vm);
    vm = NULL;
}
