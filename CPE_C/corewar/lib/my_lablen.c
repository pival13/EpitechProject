/*
** EPITECH PROJECT, 2019
** my_lablen.c
** File description:
** Created by etienne-miltgen,
*/

#include "my.h"

int my_lablen(char *str, int i)
{
    int len = 0;
    if (str[i] == ':')
        i++;
    for (; str[i] != '\0'; i++)
        len++;
    return (len);
}