/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc [WSL: Ubuntu]
** File description:
** malloc
*/

#include "malloc.h"
#include <stdio.h>

void *init_mem(bool b)
{
    static void *mem = NULL;

    if (mem == NULL) {
        mem = sbrk(getpagesize() * 2);
        ((malloc_t *)mem)->end = true;
        ((malloc_t *)mem)->free = true;
        ((malloc_t *)mem)->size = getpagesize() * 2 - sizeof(malloc_t);
    }
    if (b)
        mem = NULL;
    return mem;
}

void print_mem(void)
{
    malloc_t *mem = init_mem(false);

    while (!mem->end) {
        my_printf("%p -> ", mem);

        size_t size = mem->size;
        malloc_t *tmp = mem + 1 + mem->size / sizeof(malloc_t);
        while (!mem->end && mem->free == tmp->free) {
            mem = tmp;
            size += mem->size;
            tmp = mem + 1 + mem->size / sizeof(malloc_t);
        }
        my_printf("%x: %s\n", size, (mem->free ? "free" : "busy"));
        if (!mem->end)
            mem += 1 + mem->size / sizeof(malloc_t);
    }
    my_printf("%p -> %x: ", mem+1, mem->size);
    my_printf("%s\n\n", (mem->free ? "free" : "busy"));
}

void add_node_next(malloc_t *save, size_t size)
{
    malloc_t *tmp = save + 1 + size / sizeof(malloc_t);
    tmp->size = save->size - size - sizeof(malloc_t);
    save->size = size;
    tmp->end = save->end;
    save->end = false;
    tmp->free = true;
}
