/*
** EPITECH PROJECT, 2020
** ftrace [WSL: Ubuntu]
** File description:
** ftrace
*/

#pragma once

#include "lib/generic_list.h"

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <gelf.h>
#include <fcntl.h>
#include <stdio.h>
#include <regex.h>
#include <sys/stat.h>

#define PEEK(pid, offset) ptrace(PTRACE_PEEKTEXT, pid, offset, NULL)

enum syscall_type_s {
    NONE = -1,
    INT,
    UNSIGNED,
    LONG,
    SIZE_T,
    STRING,
    POINTER
};

typedef struct syscall_s {
    char *name;
    int return_value;
    int *params;
} syscall_t;

extern const syscall_t syscall_tab[];

typedef struct ftrace_s {
    bool begin_write;
    bool display;
    int pid;
    size_t opcode;
    list_t elfs;
    struct user_regs_struct reg;
} ftrace_t;

typedef struct shared_lib_s {
    int fd;
    bool writable[6];
    char *name;
    Elf *elf;
    size_t pos[6][3];
} shared_lib_t;

typedef struct symbol_located_s {
    size_t symb_begin;
    size_t offset;
    char *bin_name;
    char *sect_name;
    char *symb_name;
} symbol_located_t;

void my_printf(char *s, ...);
char *get_next_line(int fd);

void parent_process(ftrace_t *obj);
void search_plt(const shared_lib_t *slib, symbol_located_t *r);

void free_slib(shared_lib_t *slib);
void delete_elfs(ftrace_t *obj);
void update_elfs(ftrace_t *obj);
symbol_located_t symbol_finder(const ftrace_t *obj, size_t offset);

void display_nb(size_t nb, char *format, bool display);
void display_string(size_t pid, size_t offset, bool display);
void display_pointer(size_t offset, bool display);

void print_syscall(const ftrace_t *obj);
void print_return_syscall(const ftrace_t *obj, size_t rax);
void print_call(ftrace_t *obj, size_t offset);
void print_return(ftrace_t *obj);