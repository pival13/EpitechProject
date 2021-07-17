/*
** EPITECH PROJECT, 2019
** hunt_kill
** File description:
** hunt and kill algo
*/

#include "dante.h"

void end_corner(char **map, int line)
{
    int len = strlen(map[0]);

    if (map[line-1][len-1] == 'X')
        map[line-1][len-1] = '*';
    if (map[line-1][len-2] == '*' && map[line-2][len-1] == '*') {
        if (rand() % 2 == 0)
            map[line-1][len-2] = 'X';
        else
            map[line-2][len-1] = 'X';
    } else if (map[line-1][len-2] == 'X' && map[line-2][len-1] == 'X') {
        if (rand() % 2 == 0)
            map[line-1][len-2] = '*';
        else
            map[line-2][len-1] = '*';
    }
}

void last_line_hk(char **map)
{
    int line = 0;

    for (; map[line] != NULL; line++);
    if (strlen(map[0]) % 2 == 0)
        for (int i = 0; i < line; i += 2)
            if (rand() % 2 == 0)
                map[i][strlen(map[i])-1] = '*';
    if (line % 2 == 0)
        for (int i = 0; i < (int)strlen(map[line-1]); i += 2)
            if (rand() % 2 == 0)
                map[line-1][i] = '*';
    end_corner(map, line);
}