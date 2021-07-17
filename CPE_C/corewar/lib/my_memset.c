/*
** EPITECH PROJECT, 2019
** my_memset.c
** File description:
** Created by etienne-miltgen,
*/

#include "my.h"

void *my_memset(void *s, int c, size_t len)
{
    if (s == NULL)
        return (NULL);
    for (size_t i = 0; i < len; i++) {
        ((unsigned char *)s)[i] = c;
    }
    return (s);
}