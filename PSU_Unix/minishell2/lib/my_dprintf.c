/*
** EPITECH PROJECT, 2019
** my_dprintf
** File description:
** print only with %s and %d
*/

#include <unistd.h>
#include <stdarg.h>

static void my_dputchar(int fd, char c)
{
    int len = 1;

    len = write(fd, &c, len);
}

static void my_dprintf_next(int fd, char *str, va_list arg)
{
    char *buff;
    int nb;
    long long m = 1;

    if (str[1] == 's') {
        buff = va_arg(arg, char *);
        for (nb = 0; buff[nb] != '\0'; nb++);
        nb = write(fd, buff, nb);
    } else if (str[1] == 'c') {
        my_dputchar(fd, va_arg(arg, int));
    } else {
        nb = va_arg(arg, int);
        (nb < 0) ? (my_dputchar(fd, '-'), nb *= -1) : (nb);
        for (; m <= nb/10; m *= 10);
        for (; m > 1; m /= 10) {
            my_dputchar(fd, nb/m+'0');
            nb %= m;
        }
        my_dputchar(fd, nb+'0');
    }
}

void my_dprintf(int fd, char *str, ...)
{
    va_list arg;
    int len = 0;
    int i = 0;

    va_start(arg, str);
    for (; str[i] != '\0'; i++, len++)
        if (str[i] == '%' && (str[i+1] == 's' || str[i+1] == 'd' || str[i+1]
        == 'c')) {
            len = write(fd, &str[i-len], len);
            len = -1;
            my_dprintf_next(fd, &str[i], arg);
            i++;
        }
    len = write(fd, &str[i-len], len);
    va_end(arg);
}
