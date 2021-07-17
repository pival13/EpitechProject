/*
** EPITECH PROJECT, 2019
** convert binary
** File description:
** convert binary string to decimal
*/

#include "my.h"

void convert_binary(cell_t **map, int fd)
{
    int nb = 0;

    for (int j = 1; j != 23; j++) {
        nb = 0;
        for (int i = 1; i != 18; i++) {
            nb = nb << 1;
            nb = nb | map[j][i].known;
        }
        my_dprintf(fd, "%d", nb);
        if (j != 22)
            my_dprintf(fd, "%c", '\b');
    }
    my_dprintf(fd, "\n");
}

void convert_decimal_to_binary(map_t *map, char **map1)
{
    int nb = 0;

    for (int j = 1; j != 23; j++) {
        nb = my_getnbr(map1[j-1]);
        for (int i = 17; nb != 0; i--) {
            map->map[0][0][j][i].known = nb % 2;
            nb /= 2;
        }
    }
}
