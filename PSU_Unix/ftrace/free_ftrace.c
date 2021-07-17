/*
** EPITECH PROJECT, 2020
** ftrace [WSL: Ubuntu]
** File description:
** read_proc
*/

#include "ftrace.h"

void free_slib(shared_lib_t *slib)
{
    if (slib->elf)
        elf_end(slib->elf);
    if (slib->fd > 0)
        close(slib->fd);
    if (slib->name)
        free(slib->name);
    free(slib);
}

void delete_elfs(ftrace_t *obj)
{
    shared_lib_t *shared_lib;

    while (!list_empty(obj->elfs)) {
        shared_lib = list_get_front(obj->elfs);
        free_slib(shared_lib);
        list_pop_front(&obj->elfs);
    }
}
