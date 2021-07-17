/*
** EPITECH PROJECT, 2019
** assembler
** File description:
** convert the file into assembler language
*/

#include "my.h"

void launch_function(op_t *tab, int fd, asm_t *list, \
void (*funct[16])(op_t, asm_t *, int))
{
    for (int j = 0; j != 16; j++) {
        if (!my_strcmp(list->arg, tab[j].mnemonique))
            (*funct[j])(tab[j], list, fd);
    }
}

void assembler(asm_t *list, char *name)
{
    op_t *tab = op_tab;
    void (*funct[16])(op_t, asm_t *, int) = {asm_live, asm_funct, asm_funct, \
asm_funct, asm_funct, asm_funct, asm_funct, asm_funct, asm_zjmp_fork, \
asm_ldi, asm_sti, asm_zjmp_fork, asm_funct, asm_ldi, asm_zjmp_fork, \
asm_funct};
    int fd = return_fd(name);

    if (!list || fd == -1)
        return;
    asm_header(fd, list);
    for (; list && list->prev != NULL; list = list->prev);
    for (; list; list = list->next) {
        if (list->other == 0)
            launch_function(tab, fd, list, funct);
    }
    my_dprintf(1, "OK\n");
    close(fd);
}
