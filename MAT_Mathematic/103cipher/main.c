/*
** EPITECH PROJECT, 2018
** 103cipher
** File description:
** 
*/

#include "my.h"
#include <stdlib.h>

int main(int n, char **arg)
{
    if (n != 4 || (arg[3][0] != '0' && arg[3][0] != '1') || arg[3][1] != '\0' || arg[1][0] == '\0' || arg[2][0] == '\0')
        return (84);
    if (arg[3][0] == '0')
        crypt(arg[1], arg[2]);
    if (arg[3][0] == '1') {
        int **key = create_key(arg[2]);
        int **str = create_matrix(arg[1], key);
        decrypt(arg[1], arg[2]);
    }
    return (0);
}
