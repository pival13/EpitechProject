/*
** EPITECH PROJECT, 2019
** my_print_array.c
** File description:
** print array
*/

#include "my.h"
#include <stddef.h>

void my_print_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        my_printf("%s\n", array[i]);
    }
}
