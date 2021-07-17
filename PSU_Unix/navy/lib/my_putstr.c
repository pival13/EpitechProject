/*
** EPITECH PROJECT, 2019
** my_putstr.c
** File description:
** my_putstr
*/

#include "my.h"
#include "navy.h"
#include <unistd.h>

void my_putstr(char const *s)
{
    int len = my_strlen(s);

    write(1, s, len);
}
