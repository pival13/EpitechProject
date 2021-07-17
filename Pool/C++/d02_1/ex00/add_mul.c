/*
** EPITECH PROJECT, 2020
** add_mul.c
** File description:
** add mul
*/

#include <stdlib.h>

void add_mul_4param(int a, int b, int *sum, int *product)
{
    if (sum != NULL)
        *sum = a+b;
    if (product != NULL)
        *product = a*b;
}

void add_mul_2param(int *first, int *second)
{
    int a;
    int b;

    if (first == NULL || second == NULL)
        return;
    a = *first;
    b = *second;
    *first = a+b;
    *second = a*b;
}