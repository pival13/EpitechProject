/*
** EPITECH PROJECT, 2018
** my_swap.c
** File description:
** Function that swaps the content of two integers.
*/

void my_swap(int *a, int *b)
{
    int c = *b;
    *b = *a;
    *a = c;
}
