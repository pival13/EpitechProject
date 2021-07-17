/*
** EPITECH PROJECT, 2018
** my_putstr.c
** File description:
** Display the characters of a string.
*/

#include <unistd.h>

int my_putstr(char const *str)
{
    int n = 0;

    for (n = 0; str[n] != '\0'; n++);
    write(1, str, n);
    return (n);
}
