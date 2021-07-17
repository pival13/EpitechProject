/*
** EPITECH PROJECT, 2019
**  main
** File description:
** main of lemin
*/

#include "my.h"
#include "lemin.h"

int main(int ac, char **av)
{
    lemin_t *w;
    char **input = check_input();

    if (input == NULL) return (84);
    w = create_lemin_t(input);
    if (w == NULL) return (84);
    create_way(w);
    loop_move(w);
    return (0);
}
