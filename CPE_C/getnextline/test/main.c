/*
** EPITECH PROJECT, 2019
** main
** File description:
** main_test
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

    open("test.sh", 0, O_RDONLY);
    for (int i = 0; i != 4; i++) {
        str = get_next_line(3);
        write(1, str, strlength(str));
        write(1, "\n", 1);
        free(str);
    }
}
