/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main funcs
*/

#include "my.h"
#include "navy.h"
#include <stddef.h>

int verify_pos12_2(char *pos)
{
    for (int i = 0; i != 7; i++) {
        if (pos[i] < '1' || pos[i] > 'H'
            || pos[i] == '9')
            return (84);
        if (pos[i] > ':' && pos[i] < 'A')
            return (84);
    }
    return (0);
}

int verify_pos12(char **pos)
{
    int length;

    if (pos == NULL)
        return (84);
    for (length = 0; pos[length] != NULL; length++) {
        if (my_strlen(pos[length]) != 7)
            return (84);
        if (verify_pos12_2(pos[length]) == 84)
            return (84);
    }
    if (length != 4)
        return (84);
    return (0);
}

int main(int ac, char **av)
{
    char **pos;
    int pid;

    if (ac == 2) {
        pos = read_file(av[1]);
        if (verify_pos12(pos) == 84)
            return (84);
        return (game(pos, 1, 0));
    } else if (ac == 3) {
        pos = read_file(av[2]);
        if (verify_pos12(pos) == 84 || is_int(av[1]) == 0)
            return (84);
        pid = my_getnbr(av[1]);
        return (game(pos, 2, pid));
    } else
        return (84);
}
