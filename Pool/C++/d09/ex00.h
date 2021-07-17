/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** ex00
*/

#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct cthulhu_s {
    char *m_name;
    int m_power;
} cthulhu_t;

typedef struct koala_s {
    cthulhu_t m_parent;
    char m_is_a_legend;
} koala_t;

cthulhu_t *new_cthulhu();
void print_power(cthulhu_t *this);
void attack(cthulhu_t *this);
void sleeping(cthulhu_t *this);

koala_t *new_koala(char *name, char is_legend);
void eat(koala_t *this);