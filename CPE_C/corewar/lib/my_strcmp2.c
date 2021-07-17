/*
** EPITECH PROJECT, 2019
** my_strcmp2
** File description:
** compare end of string
*/

#include "my.h"

int my_strcmp2(char *str, char *str2)
{
    if (str2 == NULL || str == NULL)return (1);
    int size1 = my_strlen(str);
    int size2 = my_strlen(str2);

    for (; size1 != 0; size1 -= 1, size2 -= 1)
        if (str[size1] != str2[size2])return (1);
    return (0);
}
