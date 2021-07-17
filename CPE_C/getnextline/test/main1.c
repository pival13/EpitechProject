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

    if (open("test.sh", 0, O_RDONLY) == -1)
        return (84);
    for (int i = 0; i != 2; i++) {
        str = get_next_line(3);
    }
    str = get_next_line(3);
    write(1, str, strlength(str));
    free(str);
}
