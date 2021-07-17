/*
** EPITECH PROJECT, 2019
** dante
** File description:
** header of dante
*/

#ifndef DANTE_H_
#define DANTE_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include "my.h"

typedef struct solver_s {
    int **tab;
    char *map;
    int len;
    int finish;
} solver_t;

void create_map(char *filepath, solver_t *w);
void solver(solver_t *w);
void solver_b(solver_t *w, int nb);
int solved_recur(solver_t *w, int x, int y);
int solved_semi_recur(solver_t *w, int x, int y);
int solved_wall(solver_t *w, int pos[2], int prev[2]);
int solved_test(char *map, int size[2]);
int is_good_map(char *map);
void clean_map(char *map);

void not_perf(char **map);
char **initialize_map(int x, int y);
void hunt_kill(char **map);
void ellers(char **map);

int is_good_cell(char **map, int x, int y);
int is_block(char **map, int x, int y);
int is_completed(char **map);
void last_line_hk(char **map);

void change_int(int **tab, int floor, int x, int *nb);
int future_link(int **tab, int *floor, int x, int nb);
int has_link(int **tab, int floor, int x, int nb);
void pair(int **nb_tab, int i, int j, int x);
void not_pair(int **nb_tab, int i, int j, int x);

#endif
