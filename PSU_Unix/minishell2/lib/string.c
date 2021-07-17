/*
** EPITECH PROJECT, 2019
** string
** File description:
** create a string similar to my_printf
*/

#include <stdlib.h>
#include <stdarg.h>

static char *concatnb(char *s1, int nb)
{
    char *str;
    int size = 0;
    int a = 0;
    int pow = 1;
    int neg = (nb >= 0) ? 0 : 1;

    for (; s1 && s1[size]; size++);
    for (int save = (nb>0)?nb:-nb; save / 10 > 0; save /= 10, pow++, size++);
    str = malloc(sizeof(char) * (size + 2 + neg));
    for (; s1 && s1[a]; a++)
        str[a] = s1[a];
    if (neg)
        str[a] = '-';
    for (nb = (nb > 0) ? nb : -nb; pow != 0; pow--, nb /= 10)
        str[a+pow-1+neg] = nb % 10 + '0';
    str[size+1+neg] = '\0';
    free(s1);
    return (str);
}

static char *concat(char *s1, char *s2, int n)
{
    char *str;
    int size = 0;
    int a = 0;

    if (n == 0)
        return (s1);
    for (; s1 && s1[size]; size++);
    for (int i = 0; s2 && s2[i] && (n == -1 || i < n); size++, i++);
    str = malloc(sizeof(char) * (size+1));
    for (; s1 && s1[a]; a++)
        str[a] = s1[a];
    for (int i = 0; s2 && s2[i] && (n == -1 || i < n); i++)
        str[a+i] = s2[i];
    str[size] = '\0';
    if (s1)
        free(s1);
    return (str);    
}

static char *string_next(char *str, va_list arg, char *string)
{
    if (str[1] == 's')
        string = concat(string, va_arg(arg, char*), -1);
    if (str[1] == 'c')
        string = concat(string, (char[2]){va_arg(arg, int), 0}, -1);
    if (str[1] == 'd')
        string = concatnb(string, va_arg(arg, int));
    return (string);
}

char *string(char *str, ...)
{
    va_list arg;
    int len = 0;
    int i = 0;
    char *string = NULL;

    va_start(arg, str);
    for (; str[i] != '\0'; i++)
        if (str[i] == '%' && (str[i+1] == 's' || str[i+1] == 'd' || str[i+1] == 'c')) {
            string = concat(string, &str[len], i-len);
            len = i + 2;
            string = string_next(&str[i], arg, string);
            i++;
        }
    string = concat(string, &str[len], i-len);
    va_end(arg);
    return (string);
}
