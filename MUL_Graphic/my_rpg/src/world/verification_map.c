/*
** EPITECH PROJECT, 2019
** create_map
** File description:
** error gestion
*/

#include "my.h"

int verification_map(char **world)
{
    int nb_pipe = 0;
    int comp_pipe = 0;

    if (world == NULL)
        return 1;
    for (int i = 0; world[0][i] != '\0'; i++)
        (world[0][i] == '|') ? (nb_pipe++) : (0);
    for (int i = 0; world[i] != NULL; i++) {
        comp_pipe = 0;
        for (int j = 0; world[i][j] != '\0'; j++)
            if (world[i][j] == '|') {
                comp_pipe++;
            } else if ((world[i][j] > '9' || world[i][j] < '0') && world[i][j] \
!= '.' && world[i][j] != '-') {
                return 1;
            }
        if (comp_pipe != nb_pipe)
            return 1;
    }
    return 0;
}
