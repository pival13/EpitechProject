/*
** EPITECH PROJECT, 2019
** matchstick
** File description:
** main loop of matchstick
*/

#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include "matchstick.h"

void check_input_next(int *line, int *match, match_t map)
{
    if (*line == 0 || *line > map.line) {
        *line = 0;
        my_printf("Error: this line is out of range\n");
    }
    if (*line == -1 || *match == -1)
        my_printf("Error: invalid input (positive number expected)\n");
    if (*match > map.match)
        my_printf("Error: you cannot remove more than %d matches per \
turn\n", map.match);
    else if (*line > 0 && *match > get_nb_matches(map.map[*line])) {
        my_printf("Error: not enough matches on this line\n");
        *match = -1;
    }
    if (*line > 0 && *match == 0)
        my_printf("Error: you have to remove at least one match\n");
}

int check_input(int *line, int *match, match_t *map)
{
    char *str;
    write(1, "Your turn:\n", 11);
    while (*line < 1 || *match < 1 || *match > map->match) {
        write(1, "Line: ", 6);
        str = get_next_line(0);
        if (str == NULL) return (1);
        *line = my_getnbr(str);
        free(str);
        if (*line <= map->line && *line > 0) {
            write(1, "Matches: ", 9);
            str = get_next_line(0);
            if (str == NULL) return (1);
            *match = my_getnbr(str);
            free(str);
        }
        check_input_next(line, match, *map);
    }
    my_printf("Player removed %d match(es) from line %d\n", *match, *line);
    change_map(map, *line, *match);
    return (0);
}

void move_ia(match_t *m, int type)
{
    int line = 0;
    int nb = 0;

    my_printf("%s", "AI's turn...\n");
    if (type == 1)
        good_ia(m, &line, &nb);
    else if (type == 2)
        semi_random_ia(m, &line, &nb);
    else
        ia(m, &line, &nb);
    change_map(m, line, nb);
    my_printf("AI removed %d match(es) from line %d\n", nb, line);
    for (int i = 0; m->map[i] != NULL; i++)
        write(1, m->map[i], my_strlen(m->map[i]));
    if (match_present(m->map) == 1)
        write(1, "\n", 1);
}

int matchstick(match_t map)
{
    int line = 0;
    int match = 0;

    while (match_present(map.map)) {
        if (check_input(&line, &match, &map) == 1) return (0);
        for (int i = 0; map.map[i] != NULL; i++)
            write(1, map.map[i], my_strlen(map.map [i]));
        if (match_present(map.map) == 0) {
            write(1, "You lost, too bad...\n", 21);
            destroy_map(map.map);
            return (2);
        }
        write(1, "\n", 1);
        line = 0;
        match = 0;
        move_ia(&map, 1);
    }
    write(1, "I lost... snif... but I'll get you next time!!\n", 47);
    destroy_map(map.map);
    return (1);
}
