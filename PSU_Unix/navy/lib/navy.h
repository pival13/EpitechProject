/*
** EPITECH PROJECT, 2019
** navy.h
** File description:
** navy.h
*/

#ifndef NAVY_H
#define NAVY_H

typedef struct arrays_t {
    char **p1;
    char **p2;
    int id_player;
    int nb_deaths;
    int nb_kills;
} arrays_t;

arrays_t *create_arrays(void);
void destroy_arrays(arrays_t *);
arrays_t *trad_arrays(arrays_t *array, char **pos);
void get_signal(int *a, int *b, int c);
void send_signal(int pid, int a, int b);
char **read_file(char *filepath);
int game(char **pos, int id_player, int pid_other);
int get_other_pid(int pid, int player);
void set_answer(int pid, int shot);
char get_answer(int a);

int is_end(arrays_t **arrays);

void order(arrays_t *arrays, int pid_other);
void enemy_attack(arrays_t *arrays, int pid_other);

void print_navy2(char **p);
void print_navy(arrays_t *arrays);

#endif
