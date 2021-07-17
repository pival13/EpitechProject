/*
** EPITECH PROJECT, 2019
** matchstick
** File description:
** header of matchstick
*/

#include "csfml.h"

#ifndef MATCHSTICK_H_
#define MATCHSTICK_H_

#define RM_ONE(x) (get_nb_matches(m->map[i]) <= m->match && get_nb_matches \
(m->map[i]) > x)
#define SMALLEST() ((get_nb_matches(m->map[line]) < m->match) ? (get_nb_mat\
ches(m->map[line])) : (m->match))

typedef struct match_s {
    char **map;
    int line;
    int match;
} match_t;

int matchstick(match_t map);
void semi_random_ia(match_t *m, int *line, int *nb);
void ia(match_t *m, int *line, int *nb);
void random_ia(match_t *m, int *line, int *nb);
void good_ia(match_t *m, int *line, int *nb);
int get_nb_matches(char *line);
void change_map(match_t *m, int line, int match);
void destroy_map(char **map);
int match_present(char **map);
char **prepare_map(int size);
void move_ia(match_t *m, int type);
void chose_match(match_t *m, window_t *w);
void draw_match(window_t *w, match_t m);

#endif
