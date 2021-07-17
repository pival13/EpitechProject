/*
** EPITECH PROJECT, 2020
** Created by theo on 20/06/2020.
** File description:
** other_tools.c
*/

#include "my.h"

int my_getnbr(char const *str)
{
    int	i = 0;
    int n = 0;

    if (str[0] == '-' && str[1] != '\0') i++;
    while (str[i] != '\0') {
        if ((str[i] < '0' || str[i] > '9'))
            break;
        n = n + str[i] - 48;
        n = n * 10;
        i++;
    }
    n /= 10;
    if (str[0] == '-')
        return (-1 * n);
    else
        return (n);
}