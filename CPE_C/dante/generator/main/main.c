/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "dante.h"

void print_map(char **map)
{
    for (int i = 0; map != NULL && map[i] != NULL; i++) {
        printf("%s", map[i]);
        free(map[i]);
        if (map[i+1] != NULL)
            printf("\n");
    }
    free(map);
}

int main(int ac, char **av)
{
    char **tab = NULL;

    if (ac != 3 && ac != 4)
        return 84;
    for (int i = 1; i != 3; i++)
        if (!is_int(av[i]))
            return 84;
    srand(time(NULL));
    tab = initialize_map(atoi(av[1]), atoi(av[2]));
    if (tab == NULL)
        return (84);
    ellers(tab);
    if (ac == 3 || strcmp(av[3], "perfect") != 0)
        not_perf(tab);
    print_map(tab);
}