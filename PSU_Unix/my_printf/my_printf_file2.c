/*
** EPITECH PROJECT, 2018
** my_printf_file2
** File description:
** contain some function of my_printf
*/

#include <stdarg.h>
#include "my_printf.h"

int put_b(va_list arg)
{
    unsigned int nb = va_arg(arg, int);
    long long m = 1;

    for (m = 1; m <= nb/2; m *= 2);
    for (; m > 1; m /= 2) {
        my_putchar(nb/m + '0');
        nb %= m;
    }
    my_putchar(nb + '0');
}

int put_bigx(va_list arg)
{
    unsigned int nb = va_arg(arg, int);
    long long m = 1;

    for (m = 1; m <= nb/16; m *= 16);
    for (; m > 1; m /= 16) {
        (nb/m > 9) ? (my_putchar(nb/m + 'A' - 10)) : (my_putchar(nb/m + '0'));
        nb %= m;
    }
    (nb > 9) ? (my_putchar(nb + 'A' - 10)) : (my_putchar(nb + '0'));
}

int put_o(va_list arg)
{
    unsigned int nb = va_arg(arg, int);
    long long m = 1;

    for (m = 1; m <= nb/8; m *= 8);
    for (; m > 1; m /= 8) {
        my_putchar(nb/m + '0');
        nb %= m;
    }
    my_putchar(nb + '0');
}

int put_bigs(va_list arg)
{
    char *str = va_arg(arg, char *);
    int m = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < 32 || str[i] > 126) {
            m = str[i];
            my_putchar('\\');
            my_putchar(m / 64 + '0');
            my_putchar(((m % 64) / 8) + '0');
            my_putchar((m % 8) + '0');
        } else
            my_putchar(str[i]);
}

int put_x(va_list arg)
{
    unsigned int nb = va_arg(arg, int);
    int m = 1;

    for (m = 1; m <= nb/16; m *= 16);
    for (; m > 1; m /= 16) {
        (nb/m > 9) ? (my_putchar(nb/m + 'a' - 10)) : (my_putchar(nb/m + '0'));
        nb %= m;
    }
    (nb > 9) ? (my_putchar(nb + 'a' - 10)) : (my_putchar(nb + '0'));
}
