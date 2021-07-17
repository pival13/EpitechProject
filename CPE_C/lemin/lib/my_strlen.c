/*
** EPITECH PROJECT, 2019
** algo
** File description:
** algo
*/

#include <stddef.h>

int my_strlen(char const *av)
{
    int a = 0;

    if (av == NULL)
        return (a);
    for (; av[a] != '\0'; a++);
    return (a);
}
