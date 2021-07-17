/*
** EPITECH PROJECT, 2020
** PSU_strace_2019 [WSL: Ubuntu]
** File description:
** print
*/

#include "ftrace.h"

void print_syscall(const ftrace_t *obj)
{
    char *s[] = {"%d", "%u", "%ld", "%lu"};
    size_t r[] = {obj->reg.rdi, obj->reg.rsi, obj->reg.rdx, obj->reg.rcx,
        obj->reg.r8, obj->reg.r9};
    const int *f_types = syscall_tab[obj->reg.rax].params;

    if (!obj->begin_write)
        return;
    my_printf("Syscall %s(", syscall_tab[obj->reg.rax].name);
    for (size_t i = 0; f_types[i] != NONE; i++) {
        if (f_types[i] == STRING)
            display_string(obj->pid, r[i], obj->display);
        else if (f_types[i] == POINTER)
            display_pointer(r[i], obj->display);
        else
            display_nb(r[i], s[f_types[i]], obj->display);
        if (f_types[i+1] != -1)
            my_printf(", ");
    }
}

void print_return_syscall(const ftrace_t *obj, size_t rax)
{
    char *s[] = {"%d", "%u", "%ld", "%lu"};
    int f_type = syscall_tab[rax].return_value;

    if (!obj->begin_write)
        return;
    my_printf(")\t = ");
    if (f_type == STRING)
        display_string(obj->pid, obj->reg.rax, obj->display);
    else if (f_type == POINTER)
        display_pointer(obj->reg.rax, obj->display);
    else
        display_nb(obj->reg.rax, s[f_type], obj->display);
    my_printf("\n");
}

void print_call(ftrace_t *obj, size_t offset)
{
    symbol_located_t symb = symbol_finder(obj, offset);

    if (!symb.bin_name) {
        update_elfs(obj);
        symb = symbol_finder(obj, offset);
    }
    if (symb.symb_name && !strcmp(symb.symb_name, "_init"))
        obj->begin_write = true;
    if (!symb.bin_name || !obj->begin_write)
        return;
    if (symb.symb_name) {
        fprintf(stderr, "Entering function %s", symb.symb_name);
        if (symb.symb_begin != symb.offset)
            fprintf(stderr, "+0x%lx", symb.offset-symb.symb_begin);
        fprintf(stderr, " at 0x%lx (%s+0x%lx %s)\n", offset, symb.bin_name,
            symb.offset, symb.sect_name);
    } else if (symb.sect_name)
        fprintf(stderr, "Entering function 0x%lx@%s (%s) at 0x%lx\n",
            symb.offset, symb.bin_name, symb.sect_name, offset);
}

void print_return(ftrace_t *obj)
{
    symbol_located_t symb = symbol_finder(obj, obj->reg.rip);

    if (!symb.bin_name) {
        update_elfs(obj);
        symb = symbol_finder(obj, obj->reg.rip);
    }
    if (!symb.bin_name || !obj->begin_write)
        return;
    if (symb.symb_name) {
        fprintf(stderr, "Leaving function %s", symb.symb_name);
        fprintf(stderr, " at 0x%llx (%s %s)\n", obj->reg.rip, symb.bin_name,
            symb.sect_name);
    } else if (symb.sect_name)
        fprintf(stderr, "Leaving function 0x%lx@%s (%s) at 0x%llx\n",
            symb.offset, symb.bin_name, symb.sect_name, obj->reg.rip);
}