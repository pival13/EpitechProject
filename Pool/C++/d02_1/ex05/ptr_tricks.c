/*
** EPITECH PROJECT, 2020
** ptr_tricks
** File description:
** tricks related to pointers
*/

#include "ptr_tricks.h"
#include <stdio.h>

int get_array_nb_elem(const int *ptr1, const int *ptr2)
{
    return (ptr2 > ptr1 ? ptr2 - ptr1 : ptr1 - ptr2);
}

whatever_t *get_struct_ptr(const int *member_ptr)
{
    unsigned long add = (unsigned long)member_ptr;
    whatever_t *what;

    add = (unsigned long)what - (unsigned long)&what->member + add;
    return (whatever_t *)add;
}