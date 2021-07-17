/*
** EPITECH PROJECT, 2019
** my_atoi.c
** File description:
** my atoi
*/

#include "my.h"

char *my_atoi(int nbr)
{
    char *str = malloc(sizeof(char) * 14);
    int reste = 0;
    int i = 0;

    if (nbr == 0)
        return ("0");
    while (nbr != 0) {
        reste = nbr % 10;
        str[i] = reste + 48;
        nbr -= reste;
        nbr = nbr / 10;
        i++;
    }
    str[i] = 0;
    my_revstr(str);
    return (str);
}
