/*
** EPITECH PROJECT, 2019
** check_map
** File description:
** function to interact with the map
*/

#include "my.h"
#include "matchstick.h"
#include <stdlib.h>

int match_present(char **map)
{
    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j] != '\n'; j++)
            if (map[i][j] == '|')
                return (1);
    return (0);
}

int get_nb_matches(char *line)
{
    int n = 0;

    if (line == NULL || line[1] == '*') return (0);
    for (int i = 0; line[i] != '\n'; i++)
        if (line[i] == '|')
            n++;
    return (n);
}

void change_map(match_t *m, int line, int match)
{
    int nb = get_nb_matches(m->map[line]);

    for (int i = 0; i != match; i++)
        m->map[line][m->line-line+nb-i] = ' ';
}
