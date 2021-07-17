/*
** EPITECH PROJECT, 2020
** ex05.h
** File description:
** header of exercice 5
*/

#ifndef EX05_H
#define EX05_H

#include <stdint.h>

typedef union foo_s {
    union {
        uint32_t foo;
        union {
            uint32_t foo;
            uint32_t bar;
        } bar;
        uint64_t a;
    } foo;
    uint64_t bar;
} foo_t;

#endif