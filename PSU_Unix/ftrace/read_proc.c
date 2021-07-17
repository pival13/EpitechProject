/*
** EPITECH PROJECT, 2020
** ftrace [WSL: Ubuntu]
** File description:
** read_proc
*/

#include "ftrace.h"

static int contain_lib(shared_lib_t *shared_lib, char *name)
{
    return strcmp(shared_lib->name, name);
}

static void edit_name(ftrace_t *obj)
{
    char *s;
    shared_lib_t *slib;

    for (size_t i = 0; i != list_size(obj->elfs); i++) {
        slib = list_get(obj->elfs, i);
        s = strdup(strrchr(slib->name, '/') + 1);
        free(slib->name);
        slib->name = s;
    }
}

static void fill_slib(shared_lib_t *slib, char *str, regmatch_t *rm)
{
    for (int i = 0; i != 6; i++) {
        if (slib->pos[i][1] != 0)
            continue;
        slib->pos[i][0] = strtoul(str+rm[1].rm_so, NULL, 16);
        slib->pos[i][1] = strtoul(str+rm[2].rm_so, NULL, 16);
        slib->writable[i] = (str[rm[3].rm_so + 1] != '-');
        slib->pos[i][2] = strtoul(str+rm[4].rm_so, NULL, 16);
        if (!slib->name)
            slib->name = strdup(str + rm[5].rm_so);
        return;
    }
}

static void parse_proc_line(ftrace_t *obj, char *str, regex_t re)
{
    regmatch_t rm[6] = {0};
    shared_lib_t *shared_lib;

    if (!regexec(&re, str, 6, rm, REG_NOTEOL) && str[rm[3].rm_so] != '-') {
        shared_lib = (shared_lib_t*)list_get_first_node_with_value(obj->elfs,
            str + rm[5].rm_so, (value_comparator_t)contain_lib);
        if (!shared_lib) {
            shared_lib = malloc(sizeof(shared_lib_t));
            if (!shared_lib)
                return free_slib(shared_lib);
            memset(shared_lib, 0, sizeof(shared_lib_t));
            fill_slib(shared_lib, str, rm);
            shared_lib->fd = open(shared_lib->name, O_RDONLY);
            shared_lib->elf = elf_begin(shared_lib->fd, ELF_C_READ, NULL);
            if (!shared_lib->elf)
                return free_slib(shared_lib);
            list_push_front(&obj->elfs, shared_lib);
        } else
            fill_slib(((node_t*)shared_lib)->value, str, rm);
    }
}

void update_elfs(ftrace_t *obj)
{
    char s[20] = {0};
    regex_t re;
    char *str;
    int fd;

    snprintf(s, 19, "/proc/%d/maps", obj->pid);
    fd = open(s, O_RDONLY);
    if (fd == -1)
        error(84, errno, "%s", s);
    if (regcomp(&re, "(\\w+)-(\\w+) (..).. (\\w+) .{5,} \\w+ +(/)",REG_EXTENDED))
        error(84, errno, "Regex compilation failed\n");

    delete_elfs(obj);
    for (str = get_next_line(fd); str != NULL; str = get_next_line(fd)) {
        parse_proc_line(obj, str, re);
        free(str);
    }
    edit_name(obj);
    regfree(&re);
    close(fd);
}
