/*
** EPITECH PROJECT, 2019
** clean_str.c
** File description:
** clean str
*/

#include "my.h"

void clean_str(char *str)
{
    int len = my_strlen(str);

    for (int i = 0; i < len; i++)
        str[i] = 0;
}
