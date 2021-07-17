/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc [WSL: Ubuntu]
** File description:
** malloc
*/

#pragma once

#include <unistd.h>
#include <stdbool.h>

typedef struct malloc_s {
    size_t size;
    bool free;
    bool end;
} malloc_t;

void my_printf(char *str, ...);
void *init_mem(bool);
void *malloc(size_t size);
void free(void *ptr);
void print_mem(void);
void add_node_next(malloc_t *save, size_t size);