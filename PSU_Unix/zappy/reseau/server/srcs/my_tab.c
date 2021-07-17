/*
** EPITECH PROJECT, 2020
** Created by theo on 18/05/2020.
** File description:
** my_tab.c
*/

#include "my.h"

static char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    for (; i <= n; i++) {
        dest[i] = src[i];
        if (n == i)
            dest[n] = '\0';
    }
    return (dest);
}

static int nb_lines(char const *str, char c)
{
    int i = 0;
    int nb = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] == c && str[i + 1] != '\0')
            nb++;
    }
    return (nb);
}

static int condition(char c, char cond)
{
    if (c != '\0') {
        if (c != cond)
            return (1);
    }
    return (0);
}

char **my_tab(char const *buffer, char c)
{
    char **tab = NULL;
    int i = 0;
    int a = 0;
    int b = 0;

    tab = my_malloc(sizeof(char *) * (nb_lines(buffer, c) + 2));
    while (buffer[b] != '\0') {
        for (a = 0; condition(buffer[a + b], c); a++);
        if (a != 0) {
            tab[i] = my_malloc(sizeof(char) * (a + 1));
            my_strncpy(tab[i], buffer + b, a);
            tab[i][a] = '\0';
            i++;
            b += a;
        }
        if (buffer[b] != '\0') b++;
    }
    tab[i] = NULL;
    return (tab);
}

void free_tab(char **tab)
{
    for (int i = 0; tab[i]; i++)
        my_free(tab[i]);
    my_free(tab);
}