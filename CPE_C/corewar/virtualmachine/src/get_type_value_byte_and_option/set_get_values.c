/*
** EPITECH PROJECT, 2019
** set_get_value.c
** File description:
** set or get the value wait
*/

#include "my.h"

static int size_arg(unsigned char type, int nb)
{
    int size[3] = {1, DIR_SIZE, IND_SIZE};
    int nbr = (type >> (6 - 2 * nb)) & 3;

    return (size[nbr-1]);
}

unsigned int get_value(virtualmachine_t *vm, int champ, int nb)
{
    int size = size_arg(vm->memory[(vm->champion[champ].pc + 1) \
% MEM_SIZE], nb - 1);
    int pos = (vm->champion[champ].pc + 2);
    unsigned int value = 0;
    unsigned int reg = 0;

    for (int i = 0; i != nb - 1; i++)
        pos += size_arg(vm->memory[(vm->champion[champ].pc + 1) \
% MEM_SIZE], i);
    reg = get_bytes(vm->memory, pos, size);
    if (size == 1)
        value = get_bytes(vm->champion[champ].reg, REG_SIZE * (reg - 1), \
REG_SIZE);
    else if (size == 2)
        value = get_bytes(vm->memory, pos + reg % IDX_MOD, size);
    else
        value = reg;
    return (value);
}

void set_value(virtualmachine_t *vm, int champ, int nb, unsigned int number)
{
    int size = size_arg(vm->memory[(vm->champion[champ].pc + 1) % \
MEM_SIZE], nb - 1);
    int pos = vm->champion[champ].pc + 2;
    unsigned int reg = 0;

    for (int i = 0; i != nb - 1; i++)
        pos += size_arg(vm->memory[(vm->champion[champ].pc + 1) \
% MEM_SIZE], i);
    reg = get_bytes(vm->memory, pos, size);
    if (size == 1 && reg > 0 && reg < REG_NUMBER + 1)
        set_bytes(vm->champion[champ].reg, number, REG_SIZE * (reg - 1), \
REG_SIZE);
    else if (size != 1)
        set_bytes(vm->memory, number, vm->champion[champ].pc + reg % \
IDX_MOD, REG_SIZE);
}
