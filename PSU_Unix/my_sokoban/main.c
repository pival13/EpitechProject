/*
** EPITECH PROJECT, 2018
** main sokoban
** File description:
** main of sokoban
*/

#include "sokoban.h"
#include "my.h"

int sokoban(char *arg, int nb_j);

int main(int n, char **arg)
{
    if (n != 2)
        return (84);
    if (my_strcmp(arg[1], "-h") == 0) {
        my_putstr(USAGE);
        return (0);
    }
    sokoban(arg[1], 1);
}
