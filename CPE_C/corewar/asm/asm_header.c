/*
** EPITECH PROJECT, 2019
** ass_header
** File description:
** header of the assembler
*/

#include "my.h"

static int find_size_header(asm_t *list)
{
    int size = 0;

    while (list) {
        size += list->size;
        list = list->next;
    }
    return (size);
}

void asm_header(int fd, asm_t *list)
{
    asm_t *mem;
    int size = find_size_header(list);

    print_nb(fd, COREWAR_EXEC_MAGIC, 4);
    for (mem = list; mem && mem->other != 1; mem = mem->next);
    my_writer(fd, mem->arg, PROG_NAME_LENGTH);
    print_nb(fd, size, 8);
    for (mem = list; mem && mem->other != 2; mem = mem->next);
    my_writer(fd, mem->arg, COMMENT_LENGTH);
    print_nb(fd, 0, 4);
}