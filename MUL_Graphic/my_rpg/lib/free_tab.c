/*
** EPITECH PROJECT, 2019
** free_tab
** File description:
** free a tab
*/

#include <stdlib.h>

void free_tab(char **tab)
{
    free(tab[0]);
    free(tab);
}

void free_tab3(char ***tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        free_tab(tab[i]);
    free(tab);
}