/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc [WSL: Ubuntu]
** File description:
** malloc
*/

#include "malloc.h"
#include <stdio.h>

static void merge_free(malloc_t *mem)
{
    malloc_t *next = mem + 1 + mem->size / sizeof(malloc_t);
    while (!next->end && mem->free && next->free) {
        mem->size += next->size + sizeof(malloc_t);
        next += 1 + next->size / sizeof(malloc_t);
    }
    if (next->free && mem->free) {
        mem->size += next->size + sizeof(malloc_t);
        mem->end = true;
    }
}

void free(void *ptr)
{
    malloc_t *mem = ptr - sizeof(malloc_t);

    if (ptr == NULL)
        return;
    mem->free = true;
    mem = init_mem(false);
    while (!mem->end) {
        merge_free(mem);
        if (!mem->end)
            mem += 1 + mem->size / sizeof(malloc_t);
    }
    if (mem->size > getpagesize() * (size_t)2) {
        sbrk(-getpagesize() * 2);
        mem->size -= getpagesize() * 2;
        if (mem == init_mem(false))
            init_mem(true);
    }
}
