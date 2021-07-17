/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "get_next_line.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int my_strlen(char *str);

int main(int n, char **arg)
{
    char *str;

    if (open("../get_next_line.c", 0, O_RDONLY) == -1)
        return (84);
    str = get_next_line(3);
    while (str != NULL) {
        write(1, str, strlength(str));
        write(1, "\n", 1);
        free(str);
        str = get_next_line(3);
    }
}
