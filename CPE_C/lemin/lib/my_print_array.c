/*
** EPITECH PROJECT, 2019
** my_print_array.c
** File description:
** my print array
*/

#include "my.h"

void my_print_array(char **arr)
{
    int i = 0;

    for (i = 0; arr[i] != NULL; i++)
        my_printf("%s\n", arr[i]);
}
