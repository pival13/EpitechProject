/*
** EPITECH PROJECT, 2019
** print_nb.c
** File description:
** print a number
*/

#include "my.h"

void print_nb(int fd, unsigned int nb, int nb_bytes)
{
    long long div = 1;

    for (int i = 1; i != nb_bytes; i++)
        div *= 256;
    for (int i = 0; i != nb_bytes; i++) {
        my_dprintf(fd, "%c", ((nb / div) % 256));
        div /= 256;
    }
}
