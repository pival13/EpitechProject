/*
** EPITECH PROJECT, 2019
** move_ia
** File description:
** change the board depending of the ia
*/

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "my.h"
#include "matchstick.h"

void random_ia(match_t *m, int *line, int *nb)
{
    *line = 0;
    *nb = 0;
    while (*line == 0) {
        *line = (random() % m->line) + 1;
        if (get_nb_matches(m->map[*line]) == 0)
            *line = 0;
    }
    while (*nb == 0)
        *nb = (random() % ((get_nb_matches(m->map[*line]) < m->match) ? \
(get_nb_matches(m->map[*line])) : (m->match)) + 1);
}

void semi_random_ia(match_t *m, int *line, int *nb)
{
    *line = 0;
    *nb = 0;
    for (int i = 0; *line == 0; i++) {
        *line = (random() % m->line) + 1;
        if (get_nb_matches(m->map[*line]) < 2)
            *line = 0;
        if (i > 500)
            return (random_ia(m, line, nb));
    }
    for (int i = 0; *nb == 0; i++)
        *nb = (random() % ((get_nb_matches(m->map[*line]) < m->match) ? \
(get_nb_matches(m->map[*line])) : (m->match)) + 1);
}

void good_ia_3(match_t *m, int *line, int *nb, int lines[2])
{
    if (lines[1] == 1) {
        semi_random_ia(m, line, nb);
        *nb = (get_nb_matches(m->map[*line]) - 1) % (m->match+1);
        if (*nb == 0)
            *nb = 1;
        return;
    }
    for (int i = m->line; i != 0; i--)
        if (get_nb_matches(m->map[i]) <= m->match + 1 && get_nb_\
matches(m->map[i]) > 1) {
            *line = i;
            *nb = get_nb_matches(m->map[i]) - 1;
            return;
        }
    semi_random_ia(m, line, nb);
}

void good_ia_2(match_t *m, int *line, int *nb, int lines[2])
{
    if (lines[0] % 2 == 0) {
        for (int i = m->line; i != 0; i--)
            if (get_nb_matches(m->map[i]) <= m->match && get_nb_\
matches(m->map[i]) > 1) {
                *line = i;
                *nb = get_nb_matches(m->map[i]);
                return;
            }
        for (int i = m->line; i != 0; i--)
            if (get_nb_matches(m->map[i]) <= m->match && get_nb_\
matches(m->map[i]) > 0) {
                *line = i;
                *nb = get_nb_matches(m->map[i]);
                return;
            }
    }
    return (good_ia_3(m, line, nb, lines));
}

void good_ia(match_t *m, int *line, int *nb)
{
    int lines[2] = {0, 0};

    for (int i = 0; m->map[i] != NULL; i++)
        if (get_nb_matches(m->map[i]) != 0)
            lines[0]++;
    for (int i = 0; m->map[i] != NULL; i++)
        if (RM_ONE(0))
            lines[1]++;
    if (lines[0] == 1) {
        random_ia(m, line, nb);
        *nb = (get_nb_matches(m->map[*line]) - 1) % (m->match+1);
        if (*nb == 0)
            *nb = 1;
        return;
    }
    return (good_ia_2(m, line, nb, lines));
}
