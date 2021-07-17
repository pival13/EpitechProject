/*
** EPITECH PROJECT, 2018
** my_show_word_array.c
** File description:
** Function that displays the content of a words array.
*/

#include "../../include/my.h"

int my_show_word_array(char * const *tab)
{
    for (int i = 0; tab[i] != 0; i++) {
        my_putstr(tab[i]);
        my_putchar('\n');
    }
}
