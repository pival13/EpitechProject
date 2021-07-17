/*
** EPITECH PROJECT, 2018
** my_printf_file1
** File description:
** contain some function of my_printf
*/

#include <stdarg.h>
#include "my_printf.h"

int put_c(va_list arg)
{
    my_putchar(va_arg(arg, int));
}

int put_s(va_list arg)
{
    char *str = va_arg(arg, char *);
    int n = 0;

    for (n; str[n] != '\0'; n++)
        my_putchar(str[n]);
}

int put_d(va_list arg)
{
    int nb = va_arg(arg, int);
    long long m = 1;

    (nb < 0) ? (my_putchar('-'), nb *= -1) : (nb);
    for (m = 1; m <= nb/10; m *= 10);
    for (m; m > 1; m /= 10) {
        my_putchar(nb/m + '0');
        nb %= m;
    }
    my_putchar(nb + '0');
}

int put_percent(va_list arg)
{
    my_putchar('%');
}

int put_p(va_list arg)
{
    unsigned long long nb = va_arg(arg, long long);
    long long m = 1;

    my_putchar('0');
    my_putchar('x');
    for (m = 1; m <= nb/16; m *= 16);
    for (m; m > 1; m /= 16) {
        (nb/m > 9) ? (my_putchar(nb/m + 'a' - 10)) : (my_putchar(nb/m + '0'));
        nb %= m;
    }
    (nb > 9) ? (my_putchar(nb + 'a' - 10)) : (my_putchar(nb + '0'));
}
