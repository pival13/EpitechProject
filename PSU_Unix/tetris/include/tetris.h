/*
** EPITECH PROJECT, 2019
** tetris.h
** File description:
** header of tetris
*/

#ifndef TETRIS_H_
#define TETRIS_H_

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ncurses.h>
#include <dirent.h>
#include <time.h>

typedef struct tetrimino_s {
    char **piece;
    int color;
    int size[2];
    char *name;
} tetrimino_t;

typedef struct tetris_s {
    tetrimino_t *piece;
    int left;
    int right;
    int down;
    int rotate;
    int exit;
    int pause;
    int next;
    int lvl;
    int size[2];
    int curr;
    int ncurr;
    float speed;
    char **map;
} tetris_t;

tetrimino_t *create_tetrimino(tetrimino_t *tetris);

int debug_mode(tetris_t *w);

int check_piece(tetrimino_t piece);

int options_tetris(tetris_t *w, char **arg, int n);
int options_1arg_set_values(tetris_t *w, char *opt, char *value);

void tetris(tetris_t *w);
void move_piece(tetris_t *w, int c);
void check_erase_line(tetris_t *w);
void rotate_piece(tetris_t *w);
void decrease_piece(tetris_t *w, int *c);
void add_piece(tetris_t *w, int *c);
void draw_tetris(tetris_t *w);
int can_move(tetris_t *w, int sens);

#endif
