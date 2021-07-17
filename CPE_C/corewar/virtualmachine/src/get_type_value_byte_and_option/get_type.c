/*
** EPITECH PROJECT, 2019
** get_type
** File description:
** get the type for vm
*/

#include "my.h"

int get_type(int size, int nb)
{
    for (int i = 0; i != 4-nb; i++)
        size = size >> 2;
    return (size & 3);
}