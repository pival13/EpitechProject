/*
** EPITECH PROJECT, 2018
** convert_base.c
** File description:
** Convert a number of a done base into another base
*/

#include <stdlib.h>
#include "my.h"

int take_size(int nb, int base, int *m)
{
    int memory;
    int size;

    for (*m = 1; nb != 0; *m *= base) {
        memory = nb % base;
        nb -= memory;
        nb /= base;
        size++;
    }
    *m /= base;
    return (size);
}

char *complete_str(int m, int number, int base, char *str)
{
    int memory;
    int i = 0;

    if (number == 0)
        return ("0");
    if (str[0] == '-')
        i = 1;
    while (m > 0) {
        memory = number % m;
        number = (number - memory) / m;
        if (number >= 10)
            str[i] = number + 55;
        else
            str[i] = number + 48;
        number = memory;
        m /= base;
        i++;
    }
    return (str);
}

char *convert_base(char const *nbr, char const *base_from, char const *base_to)
{
    int i = 0;
    int new_base = my_strlen(base_to);
    int number = my_getnbr_base(nbr, base_from);
    int nb = number;
    int m;
    char *str;

    if (number < 0) {
        number *= -1;
        i++;
    }
    nb = number;
    if (i == 1) {
        str = malloc(take_size(nb, new_base, &m) + 1);
        str[0] = '-';
    } else
        str = malloc(take_size(nb, new_base, &m));
    complete_str(m, number, new_base, str);
    return (str);
}
