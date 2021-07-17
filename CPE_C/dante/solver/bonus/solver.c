/*
** EPITECH PROJECT, 2019
** solver
** File description:
** solver of solver
*/

#include "dante.h"

int get_size(char *map, int x)
{
    int size = 0;

    if (x == 0) {
        for (int i = 0; map[i] != '\0'; i++)
            if (map[i] == '\n')
                size++;
        return (size+1);
    } else {
        for (; map[size] != '\n'; size++);
        return (size);
    }
}

void solver_b(solver_t *w, int nb)
{
    if (nb > 3 || nb < 0)
        return (my_printf("Please enter a number between 0 and 3\n"));
    if (nb == 0 && !solved_recur(w, 0, 0))
        printf("no solution found\n");
    if (nb == 1 && !solved_semi_recur(w, 0, 0))
        printf("no solution found\n");
    if (nb == 2 && !solved_wall(w, (int [2]){0, 0}, (int [2]){0, -1}))
        printf("no solution found\n");
    if (nb == 3 && !solved_test(w->map, (int [2]){get_size(w->map, 1), get\
_size(w->map, 0)}))
        printf("no solution found");
}
