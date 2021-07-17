/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** print only with %s and %d
*/

#include <unistd.h>
#include <stdarg.h>

static void my_dputchar(char c, int fd)
{
    int len = write(fd, &c, 1);

    if (len)
        return;
}

static void my_dprintf_next(int fd, char *str, va_list arg)
{
    char *buff;
    int nb = 0;
    long long m = 1;

    if (str[1] == 's') {
        buff = va_arg(arg, char *);
        for (nb = 0; buff != NULL && buff[nb] != '\0'; nb++);
        nb = write(fd, buff, nb);
    } else if (str[1] == 'c')
        my_dputchar(va_arg(arg, int), fd);
    else {
        nb = va_arg(arg, int);
        (nb < 0) ? (write(fd, "-", 1), nb *= -1) : (nb);
        for (; m <= nb/10; m *= 10);
        for (; m > 1; nb %= m, m /= 10)
            my_dputchar(nb/m+'0', fd);
        my_dputchar(nb+'0', fd);
    }
}

void my_dprintf(int fd, char *str, ...)
{
    va_list arg;
    int len = 0;
    int i = 0;

    va_start(arg, str);
    for (; str[i] != '\0'; i++, len++)
        if (str[i] == '%' && (str[i+1] == 's' || str[i+1] == 'd' || str[i+1] =\
= 'c')) {
            write(fd, &str[i-len], len);
            len = -1;
            my_dprintf_next(fd, &str[i], arg);
            i++;
        }
    write(fd, &str[i-len], len);
    va_end(arg);
}
