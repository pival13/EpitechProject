/*
** EPITECH PROJECT, 2018
** my_getnbr_base.c
** File description:
** Convert a given base number into a decimal number
*/

#include "my.h"

int convertbase(char const *str, int i, int n)
{
    int nb = 0;
    int mem = 0;
    int max = 0;
    int maxmin = 0;
    int minmax = '0';
    
    if (i >= 11) {
        maxmin = '9';
        minmax = 'A';
        max = i + 54;
    } else {
        maxmin = i + 47;
        max = i + 47;
    }
    while (str[n] >= '0' && str[n] <= maxmin || str[n] >= minmax && str[n] <= max) {
        if (str[n] <= '9')
            mem = str[n] - 48;
        else
            mem = str[n] - 55;
        nb = nb * i + mem;
        n++;
    }
    return (nb);
}

int my_getnbr_base(char const *str, char const *base)
{
    int i = 0;
    int n = 0;
    int neg = 0;
    int nb = 0;
    int mem;
    int max = 0;
    int minmax = '0';
    int maxmin = 0;

    while (base[i] != '\0')
        i++;
    while (str[n] == '-' || str[n] == '+') {
        if (str[n] == '-') {
            neg += 1;
        }
        n += 1;
    }
    nb = convertbase(str, i, n);
    if (neg % 2 == 1)
        nb *= -1;
    return (nb);
}
