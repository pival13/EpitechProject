/*
** EPITECH PROJECT, 2019
** my_strlen
** File description:
** return the length of the string
*/

#include <stdlib.h>

int my_strlen(char const *str)
{
    int n = 0;

    if (str == NULL || str[0] == '\0' || str[0] == '\n')
        return (0);
    for (n = 1; str[n-1] != '\n' && str[n-1] != '\0'; n++);
    return (n);
}
