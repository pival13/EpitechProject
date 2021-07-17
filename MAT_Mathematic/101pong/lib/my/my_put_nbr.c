/*
** EPITECH PROJECT, 2018
** my_put_nbr.c
** File description:
** Function that displays the number given as an argument.
*/

#include "../../include/my.h"

int my_put_nbr(int nb)
{
    int reste = 0;
    char *nbr = malloc(sizeof(char) * 13);
    int n = 0;

    if (nb == 0)
        my_putchar('0');
    if (nb < 0) {
        my_putchar('-');
        nb = nb * (-1);
    }
    for (int i = 0; nb > 0; i++) {
        reste = nb % 10;
        nbr[i] = reste + 48;
        nb -= reste;
        nb /= 10;
        n++;
    }
    for (int i = n-1; i >= 0; i--)
        my_putchar(nbr[i]);
    return (0);
}
