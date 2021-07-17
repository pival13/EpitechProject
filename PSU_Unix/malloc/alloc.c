/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc [WSL: Ubuntu]
** File description:
** malloc
*/

#include "malloc.h"
#include <stdio.h>

void *calloc(size_t nmemb, size_t size)
{
    void *mem = malloc(nmemb * size);

    if (mem == NULL)
        return NULL;
    for (size_t i = 0; i != nmemb * size; i++)
        ((char *)mem)[i] = 0;
    return mem;
}

static void merge_realloc(malloc_t *mem, size_t size)
{
    while (size > mem->size && !mem->end) {
        malloc_t *tmp = mem + 1 + mem->size / sizeof(malloc_t);
        if (!tmp->free)
            return;
        mem->size += tmp->size + sizeof(malloc_t);
        if (tmp->end)
            mem->end = true;
    }
}

void *realloc(void *ptr, size_t size)
{
    if (size % sizeof(malloc_t) != 0)
        size += sizeof(malloc_t) - (size % sizeof(malloc_t));
    if (ptr == NULL)
        return malloc(size);
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    void *mem = ptr - sizeof(malloc_t);
    merge_realloc(mem, size);
    if (size > ((malloc_t *)mem)->size) {
        char *mem2 = malloc(size);
        for (size_t i = 0; mem2 != NULL && i != ((malloc_t *)mem)->size; i++)
            mem2[i] = *(char *)(mem + sizeof(malloc_t) + i);
        free(ptr);
        ptr = mem2;
    } else if (((malloc_t *)mem)->size > size + sizeof(malloc_t))
        add_node_next(mem, size);
    return ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    return realloc(ptr, nmemb * size);
}