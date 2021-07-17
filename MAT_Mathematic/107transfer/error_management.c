/*
** EPITECH PROJECT, 2019
** error_management.c
** File description:
** error management
*/

#include "my.h"

int error_management(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
        for (int j = 0; av[i][j] != '\0'; j++) {
            if (av[i][j] != '*' && av[i][j] != '.' && av[i][j] != '-' && (av[i][j] < '0' || av[i][j] > '9')) {
                return (84);
            }
        }
    return (0);
}
