/*
** EPITECH PROJECT, 2018
** BSQ
** File description:
** find the biggest square
*/

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"

char **load_2d_arr_from_file(char *);

int is_square_of_size(char **, int, int, int);

char **draw_biggest_square(char **map, int row, int col, int size)
{
    for (int i = 0; i != size; i++)
        for (int j = 0; j != size; j++)
            map[row + i][col + j] = 'x';
    return (map);
}

char **find_the_biggest_square(char **map, int full_size[2], int size[2], int n)
{
    int mem_row = size[0];
    int mem_col = size[1];

    while (size[0] < full_size[0]) {
        if (size[1] == full_size[1]) {
            size[1] = 0;
            size[0]++;
        }
        if (size[0] + n + 1 > full_size[0] || size[1] + n + 1 > full_size[1]) {
            size[0]++;
            size[1] = 0;
        } else if (is_square_of_size(map, size[0], size[1], n+1) != 0)
            return (find_the_biggest_square(map, full_size, size, n+1));
        else
            size[1]++;
    }
    map = draw_biggest_square(map, mem_row, mem_col, n);
    return (map);
}

int main(int n, char **arg)
{
    int full_size[2] = {0, 0};
    int size[2] = {1, 0};

    (n != 2) ? exit(84) : n;
    char **map = load_2d_arr_from_file(arg[1]);
    (my_str_isnum(map[0]) == 0) ? exit(84) : map[0];
    for (full_size[0] = 0; map[full_size[0]] != NULL; full_size[0]++);
    (full_size[0] != my_getnbr(map[0]) + 1) ? exit(84) : map[0];
    for (int i = 1; map[i+1] != NULL; i++)
        (my_strlen(map[i]) != my_strlen(map[i+1])) ? exit(84) : map[i];
    for (full_size[1] = 0; map[1][full_size[1]] != '\n'; full_size[1]++);
    map = find_the_biggest_square(map, full_size, size, 0);
    for (int k = 1; map[k] != NULL; k++)
        write(1, map[k], my_strlen(map[k]));
    for (int k = 0; k != full_size[0]; k++)
        free(map[k]);
    free(map);
    return (0);
}
