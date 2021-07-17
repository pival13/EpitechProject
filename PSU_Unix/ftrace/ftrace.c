/*
** EPITECH PROJECT, 2020
** PSU_strace_2019 [WSL: Ubuntu]
** File description:
** main
*/

#include "ftrace.h"

static bool test_ff2_special(ftrace_t *obj, size_t opcode)
{
    size_t offset = 0;
    unsigned char op = (opcode >> 4*2);

    if ((op == 0x14 || op == 0x54 || op == 0x94) && (char)(opcode >> 4*4) !=
        0x24)
        return true;
    if (op == 0x14)
        offset = PEEK(obj->pid, obj->reg.rsp);
    if (op == 0x15)
        offset = PEEK(obj->pid, obj->reg.rip + 6 + (int)(opcode >> 4*4));
    if (op == 0x54)
        offset = PEEK(obj->pid, obj->reg.rsp + (char)(opcode >> 4*6));
    if (op == 0x94)
        offset = PEEK(obj->pid, obj->reg.rsp + (int)(opcode >> 4*6));
    if (offset) {
        print_call(obj, offset);
        return true;
    }
    return false;
}

static void test_ff2_call(ftrace_t *obj, size_t opcode)
{
    size_t r[8] = {obj->reg.rax, obj->reg.rcx, obj->reg.rdx, obj->reg.rbx,
                obj->reg.rsp, obj->reg.rbp, obj->reg.rsi, obj->reg.rdi};
    size_t offset = 0;
    unsigned char op = (opcode >> 4*2);

    if (test_ff2_special(obj, opcode))
        return;
    for (int j = 0; j != 8; j++) {
        if (op == j + 0x10)
            offset = PEEK(obj->pid, r[j]);
        if (op == j + 0x50)
            offset = PEEK(obj->pid, r[j] + (char)(opcode >> 4*4));
        if (op == j + 0x90)
            offset = PEEK(obj->pid, r[j] + (int)(opcode >> 4*4));
        if (op == j + 0xD0)
            offset = r[j];
        if (offset)
            return print_call(obj, offset);
    }
}

static void check_step(ftrace_t *obj)
{
    static size_t old_rax = 0;

    if (ptrace(PTRACE_GETREGS, obj->pid, NULL, &obj->reg))
        error(84, errno, "GETREGS)");
    if ((obj->opcode & 0xFFFF) == 0x050F) {
        print_return_syscall(obj, old_rax);
        if (!strcmp(syscall_tab[old_rax].name, "execve"))
            update_elfs(obj);
    }
    obj->opcode = PEEK(obj->pid, obj->reg.rip);
    if ((obj->opcode & 0xFFFF) == 0x050F)
        print_syscall(obj);
    if ((obj->opcode & 0xFF) == 0xE8)
        print_call(obj, obj->reg.rip + 5 + (int)(obj->opcode >> 4*2));
    if ((obj->opcode & 0xFF) == 0xFF)
        test_ff2_call(obj, obj->opcode);
    if ((obj->opcode & 0xFFFF) == 0xC3F3 || (obj->opcode & 0xFF) == 0xC3)
        print_return(obj);
    old_rax = obj->reg.rax;
}

void parent_process(ftrace_t *ftrace)
{
    int ret;

    elf_version(EV_CURRENT);
    if (ptrace(PTRACE_ATTACH, ftrace->pid, NULL, NULL))
        error(84, errno, "ATTACH, %d)", ftrace->pid);
    waitpid(ftrace->pid, &ret, 0);
    update_elfs(ftrace);
    while (!WIFEXITED(ret)) {
        check_step(ftrace);
        if (ptrace(PTRACE_SINGLESTEP, ftrace->pid, NULL, NULL))
            error(84, errno, "SINGLESTEP)");
        wait4(ftrace->pid, &ret, 0, NULL);
    }
    if ((ftrace->opcode & 0xFFFF) == 0x050F)
        my_printf(")\t = ?\n");
    delete_elfs(ftrace);
}
