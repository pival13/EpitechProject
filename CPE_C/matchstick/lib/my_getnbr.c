/*
** EPITECH PROJECT, 2019
** my_getnbr
** File description:
** convert a string into a number
*/

#include <stdlib.h>

int my_getnbr(char const *str)
{
    int n = 0;
    int nb = 0;

    if (str == NULL || str[0] == '\0' || str[0] == '\n')
        return (-1);
    for (; str[n] <= '9' && str[n] >= '0'; n++)
        nb = nb * 10 + (str[n] - '0');
    if (str[n] != '\0')
        return (-1);
    return (nb);
}
