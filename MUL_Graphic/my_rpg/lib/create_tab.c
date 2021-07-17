/*
** EPITECH PROJECT, 2019
** create_tab.c
** File description:
** create_tab
*/

#include "my.h"

char **create_tab(int size)
{
    char **tab = malloc(sizeof(char *) * (size + 1));

    for (int i = 0; i <= size; i++) {
        tab[i] = NULL;
    }
    return (tab);
}
