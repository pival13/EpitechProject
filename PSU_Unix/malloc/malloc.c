/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc [WSL: Ubuntu]
** File description:
** malloc
*/

#include "malloc.h"
#include <stdio.h>

size_t find_maxsize(void)
{
    size_t size = 0;
    malloc_t *mem = init_mem(false);

    while (!mem->end) {
        if (mem->free && mem->size > size)
            size = mem->size;
        mem += 1 + mem->size / sizeof(malloc_t);
    }
    if (mem->free && mem->size > size)
        size = mem->size;
    return size;
}

int increase_size(size_t size)
{
    malloc_t *mem = init_mem(false);
    int pagesize = getpagesize() * 2;
    size_t nbpage;

    while (!mem->end)
        mem += 1 + mem->size / sizeof(malloc_t);
    if (mem->free)
        size -= mem->size;
    nbpage = (size % pagesize == 0 ? (size/pagesize) : (size/pagesize) +1);
    if (sbrk(nbpage * pagesize) == (void *)-1)
        return -1;
    if (!mem->free) {
        mem->end = false;
        mem += 1 + mem->size / sizeof(malloc_t);
        mem->end = true;
        mem->free = true;
        mem->size = nbpage * pagesize - sizeof(malloc_t);
    } else
        mem->size += nbpage * pagesize;
    return 0;
}

void *alloc_better_place(size_t size)
{
    malloc_t *mem = init_mem(false);
    malloc_t *save = NULL;

    while (!mem->end) {
        if (mem->free && mem->size >= size &&
            (save == NULL || mem->size < save->size))
            save = mem;
        mem += 1 + mem->size / sizeof(malloc_t);
    }
    if (mem->free && mem->size >= size &&
        (save == NULL || mem->size < save->size))
        save = mem;
    if (save == NULL)
        return NULL;
    if (save->size > size + sizeof(malloc_t))
        add_node_next(save, size);
    save->free = false;
    return save + sizeof(malloc_t) / sizeof(malloc_t);
}

void *malloc(size_t size)
{
    if (size % sizeof(malloc_t) != 0)
        size += sizeof(malloc_t) - (size % sizeof(malloc_t));
    if (size > find_maxsize())
        if (increase_size(size) == -1)
            return NULL;
    return alloc_better_place(size);
}
