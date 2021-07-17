/*
** EPITECH PROJECT, 2020
** PSU_strace_2019 [WSL: Ubuntu]
** File description:
** main
*/

#include "strace.h"

void child_process(int n, char **arg)
{
    char **arr = malloc(sizeof(char *) * (n));
    if (arr == NULL)
        return;
    for (int i = 0; i != n-1; i++)
        arr[i] = arg[i+1];
    arr[n-1] = NULL;
    execvp(arg[1], arr);
    free(arr);
}

static void print_syscall(int pid, struct user_regs_struct reg, bool display)
{
    char *s[] = {"%d", "%u", "%ld", "%lu"};
    size_t r[] = {reg.rdi, reg.rsi, reg.rdx, reg.rcx, reg.r8, reg.r9};
    const int *f_types = syscall_x[reg.rax*3+2];

    my_printf("%s(", (char *)syscall_x[reg.rax*3]);
    for (size_t i = 0; f_types[i] != -1; i++) {
        if (f_types[i] == STRING)
            display_string(pid, r[i], display);
        else if (f_types[i] == POINTER)
            display_pointer(r[i], display);
        else
            display_nb(r[i], s[f_types[i]], display);
        if (f_types[i+1] != -1)
            my_printf(", ");
    }
}

static void print_return(int pid, struct user_regs_struct reg, size_t rax,
                            bool display)
{
    char *s[] = {"%d", "%u", "%ld", "%lu"};
    int f_type = (int)syscall_x[rax*3+1];

    my_printf(")\t = ");
    if (f_type == STRING)
        display_string(pid, reg.rax, display);
    else if (f_type == POINTER)
        display_pointer(reg.rax, display);
    else
        display_nb(reg.rax, s[f_type], display);
    my_printf("\n");
}

static int check_syscall(int pid, bool display)
{
    static unsigned short op_code = 0;
    static size_t old_rax = 0;
    struct user_regs_struct reg;

    if (ptrace(PTRACE_GETREGS, pid, NULL, &reg))
        error(84, errno, "ptrace(PTRACE_GETREGS)");
    if (op_code == 0x050F)
        print_return(pid, reg, old_rax, display);
    op_code = ptrace(PTRACE_PEEKTEXT, pid, reg.rip, NULL);
    if (op_code == 0x050F)
        print_syscall(pid, reg, display);
    old_rax = reg.rax;
    return op_code;
}

void parent_process(int pid, bool display)
{
    int ret;
    unsigned short op_code = 0;

    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL))
            error(84, errno, "ptrace(PTRACE_ATTACH, %d)", pid);
    waitpid(pid, &ret, 0);
    while (!WIFEXITED(ret)) {
        op_code = check_syscall(pid, display);
        if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL))
            error(84, errno, "ptrace(PTRACE_SINGLESTEP)");
        wait4(pid, &ret, 0, NULL);
    }
    if (op_code == 0x050F)
        my_printf(")\t = ?\n");
}
