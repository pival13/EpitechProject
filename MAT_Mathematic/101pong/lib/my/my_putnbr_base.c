/*
** EPITECH PROJECT, 2018
** my_putnbr_base.c
** File description:
** Function that converts decimal into binary and hex.
*/

#include "../../include/my.h"

int identify(char const *base)
{
    int i = 0;
    int baseid;

    for (; base[i] != '\0'; i++);
    if (i == 2)
        baseid = 0;
    if (i == 10)
        baseid = 1;
    if (i == 16)
        baseid = 2;
    return (baseid);
}

void decimal(int nbr)
{
    char *number = malloc(50);
    int n = 0;
    int reste;

    for (int i = 10; nbr != 0; n++) {
        reste = nbr % i;
        number[n] = reste + 48;
        nbr -= reste;
        nbr = nbr / 10;
    }
    for (int i = n; i >= 0; i--) {
        my_putchar(number[i]);
    }
}

void binary(int nbr)
{
    char *number = malloc(50);
    int n;

    for (int i = 0; nbr != 0; i++) {
        if (nbr % 2 == 0) {
            number[i] = '0';
            nbr = nbr / 2;
        } else if (nbr % 2 == 1) {
            number[i] = '1';
            nbr = nbr / 2;
        }
        n++;
    }
    for (int i = n; i >= 0; i--) {
        my_putchar(number[i]);
    }
}

void hexadecimal(int nbr)
{
    char *number = malloc(50);
    int reste;
    int n;

    for (int i = 0; nbr != 0; i++) {
        reste = nbr % 16;
        if (reste > 9)
            reste = reste + 7;
        number[i] = reste + 48;
        nbr = nbr / 16;
        n++;
    }
    for (int i = n; i >= 0; i--) {
        my_putchar(number[i]);
    }
}

int my_putnbr_base(int nbr, char const *base)
{
    int baseid;

    if (nbr < 0) {
        my_putchar('-');
        nbr = nbr * (-1);
    }
    baseid = identify(base);
    if (baseid == 0)
        binary(nbr);
    if (baseid == 1)
        decimal(nbr);
    if (baseid == 2)
        hexadecimal(nbr);
}
