/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** print only with %s and %d
*/

#include <unistd.h>
#include <stdarg.h>

void my_putchar(char c)
{
    int len = 1;

    len = write(1, &c, len);
}

void my_printf_next(char *str, va_list arg)
{
    char *buff;
    int nb;
    long long m = 1;

    if (str[1] == 's') {
        buff = va_arg(arg, char *);
        for (nb = 0; buff[nb] != '\0'; nb++);
        nb = write(1, buff, nb);
    } else {
        nb = va_arg(arg, int);
        (nb < 0) ? (my_putchar('-'), nb *= -1) : (nb);
        for (; m <= nb/10; m *= 10);
        for (; m > 1; m /= 10) {
            my_putchar(nb/m+'0');
            nb %= m;
        }
        my_putchar(nb+'0');
    }
}

void my_printf(char *str, ...)
{
    va_list arg;
    int len = 0;
    int i = 0;

    va_start(arg, str);
    for (; str[i] != '\0'; i++, len++)
        if (str[i] == '%' && (str[i+1] == 's' || str[i+1] == 'd')) {
            len = write(1, &str[i-len], len);
            len = -1;
            my_printf_next(&str[i], arg);
            i++;
        }
    len = write(1, &str[i-len], len);
    va_end(arg);
}
