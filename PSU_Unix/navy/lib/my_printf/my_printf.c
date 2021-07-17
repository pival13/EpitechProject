/*
** EPITECH PROJECT, 2018
** my_printf
** File description:
** print the string
*/

#include <unistd.h>
#include <stdarg.h>
#include "my_printf.h"

int my_putchar(char c)
{
    write(1, &c, 1);
    return (0);
}

void put_u(va_list arg)
{
    unsigned int nb = va_arg(arg, int);
    unsigned int m = 1;

    for (m = 1; m <= nb / 10; m *= 10);
    for (; m > 1; m /= 10) {
        my_putchar(nb / m + '0');
        nb %= m;
    }
    my_putchar(nb + '0');
}

void put_f(va_list arg)
{
    double nb = va_arg(arg, double);
    long long integer = (long long)nb;
    long long decimal = (nb - integer) * 10000000;
    long long m = 1;

    (nb < 0) ? (integer *= -1, decimal *= -1, my_putchar('-')) : (integer);
    for (m = 1; m <= integer / 10; m *= 10);
    for (; m > 1; m /= 10) {
        my_putchar(integer / m + '0');
        integer %= m;
    }
    my_putchar(integer + '0');
    my_putchar('.');
    my_putchar(decimal/1000000%10 + '0');
    my_putchar(decimal/100000%10 + '0');
    my_putchar(decimal/10000%10 + '0');
    my_putchar(decimal/1000%10 + '0');
    my_putchar(decimal/100%10 + '0');
    my_putchar(decimal/10%10 + '0');
}

void my_printf_next(char c, va_list arg)
{
    char letter[13] = {'c', 's', 'd', '%', 'p', 'b', 'X', 'o', 'S', 'x', \
'i', 'u', 'f'};
    void (*ptr[13])(va_list) = {put_c, put_s, put_d, put_percent, put_p, \
put_b, put_bigx, put_o, put_bigs, put_x, put_d, put_u, put_f};
    int j = 0;

    for (j = 0; j <= 13; j++)
        if (letter[j] == c) {
            (*ptr[j])(arg);
            j = 99;
        }
    if (j != 100) {
        my_putchar('%');
        my_putchar(c);
    }
}

void my_printf(const char *str, ...)
{
    va_list arg;

    va_start(arg, str);
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '%') {
            i++;
            my_printf_next(str[i], arg);
        } else
            my_putchar(str[i]);
    va_end(arg);
}
