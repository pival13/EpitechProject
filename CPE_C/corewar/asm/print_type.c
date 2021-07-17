/*
** EPITECH PROJECT, 2019
** print_type
** File description:
** print the type of element next
*/

#include "my.h"

char condition_print_tab(char nb, char **line, int i)
{
    if (line[i][0] == DIRECT_CHAR)
        nb += 2;
    else if (line[i][0] == 'r')
        nb += 1;
    else
        nb += 3;
    return (nb);
}

void print_type(int fd, char **line)
{
    char nb = 0;
    int end = 0;

    for (int i = 0; i != 4; i++)
        if (!end && line[i] != NULL) {
            nb = nb << 2;
            nb = condition_print_tab(nb, line, i);
        } else {
            nb = nb << 2;
            end = 1;
        }
    my_dprintf(fd, "%c", nb);
}
