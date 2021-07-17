/*
** EPITECH PROJECT, 2019
** ia
** File description:
** ia
*/

#include "my.h"
#include "matchstick.h"
#include <stdlib.h>

void ia_2(match_t *m, int *line, int *match)
{
    for (int i = m->line; i != 0; i--)
        if (RM_ONE(1) && (get_nb_matches(m->map[i]) - 1) % (m->match+1) != 0) {
            *line = i;
            *match = get_nb_matches(m->map[i]);
            return;
        }
    for (int i = m->line; i != 0; i--)
        if (RM_ONE(1)) {
            *line = i;
            *match = get_nb_matches(m->map[i]);
            return;
        }
    for (int i = m->line; i != 0; i--)
        if (RM_ONE(0)) {
            *line = i;
            *match = get_nb_matches(m->map[i]);
            return;
        }
}

void ia(match_t *m, int *line, int *match)
{
    int a[2] = {0, 0};

    *line = 0;
    *match = 0;
    for (int i = 0; m->map[i] != NULL; i++)
        if (get_nb_matches(m->map[i]) != 0)
            a[0]++;
    for (int i = 0; m->map[i] != NULL; i++)
        if ((get_nb_matches(m->map[i]) - 1) % (m->match+1) == 0)
            a[1]++;
    if (a[0] % 2 == 0 && a[0]-a[1] <= 3)
        ia_2(m, line, match);
    for (int i = 0; i < 500 && *match == 0; i++) {
        semi_random_ia(m, line, match);
        *match = (get_nb_matches(m->map[*line]) - 1) % (m->match+1);
    }
    if (*match == 0) {
        semi_random_ia(m, line, match);
        *match = 1;
    }
}
