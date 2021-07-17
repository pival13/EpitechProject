/*
** EPITECH PROJECT, 2019
** algo
** File description:
** algo
*/

#include "my.h"

int count_argument(room_t **way)
{
    int i = 0;

    for (; way[i] != NULL; i++);
    return (i);
}

void attribut_ant_number(int room, int a, lemin_t *lemin)
{
    if (room == 0) {
        lemin->ways[a][room + 1]->boolean =
        lemin->nb_ant - lemin->ways[a][room]->ant + 1;
    } else
        lemin->ways[a][room + 1]->boolean =
        lemin->ways[a][room]->boolean;
}

void display_ant_move(lemin_t *lemin, int a, int number_argument)
{
    if (lemin->nb_ways != 0)
        my_printf(" ");
    my_printf("P%d-%s", lemin->ways[a][number_argument + 1]->boolean,
    lemin->ways[a][number_argument + 1]->name);
    lemin->nb_ways++;
}

void loop_path(lemin_t *lemin)
{
    int number_argument = 0;
    int count = 0;

    for (int a = 0; lemin->ways[a] != NULL; a++) {
        number_argument = count_argument(lemin->ways[a]) - 2;
        count = 0;
        for (; number_argument >= 0; number_argument--, count++) {
            if (lemin->ways[a][number_argument]->ant >= 1 && \
(lemin->ways[a][number_argument + 1]->ant == 0 || count == 0)) {
                attribut_ant_number(number_argument, a, lemin);
                lemin->ways[a][number_argument]->ant -= 1;
                lemin->ways[a][number_argument + 1]->ant += 1;
                display_ant_move(lemin, a, number_argument);
            }
        }
    }
}

void loop_move(lemin_t *lemin)
{
    lemin->ways[0][0]->ant = lemin->nb_ant;
    while (lemin->nb_ant != lemin->end_room->ant) {
        loop_path(lemin);
        lemin->nb_ways = 0;
        my_printf("\n");
    }
}
