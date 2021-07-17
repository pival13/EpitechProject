/*
** EPITECH PROJECT, 2019
** set_get_bytes.c
** File description:
** Created by etienne-miltgen,
*/

#include "my.h"

unsigned int get_bytes(unsigned char *mem, int begin, int size)
{
    unsigned int a = 0;

    for (int i = 0; i < size; i++) {
        a = a << 8;
        a += mem[(begin + i) % MEM_SIZE] & 255;
    }
    return (a);
}

void set_bytes(unsigned char *mem, unsigned int nb, int begin, int size)
{
    int a = nb;

    for (int i = 0; i != size; i++) {
        a = nb;
        for (int j = 0; j < size - i - 1; j++)
            a = a >> 8;
        a = a & 255;
        mem[(MEM_SIZE+ begin + i) % MEM_SIZE] = a;
    }
}
