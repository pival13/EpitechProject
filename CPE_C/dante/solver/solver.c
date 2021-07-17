/*
** EPITECH PROJECT, 2019
** solver
** File description:
** solver of solver
*/

#include "dante.h"

int is_good_map(char *map)
{
    int nb = 0;

    for (int i = 0; map[i] != '\0'; i++) {
        if (map[i] == '\n' && nb == 0)
            nb = i+1;
        else if (map[i] == '\n' && i % nb != nb-1)
                return (0);
        if (map[i] != '*' && map[i] != 'X' && map[i] != '\n')
            return (0);
    }
    return (1);
}

void solver(solver_t *w)
{
    int len = strlen(w->map);

    if (!is_good_map(w->map)) {
        my_printf("Invalid map\n");
        exit(84);
    }
    if (w->map[len-1] != '*' || w->map[0] != '*')
        return (my_printf("no solution found"));
    if (!solved_recur(w, 0, 0))
        printf("no solution found");
}
