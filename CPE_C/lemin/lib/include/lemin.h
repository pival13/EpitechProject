/*
** EPITECH PROJECT, 2019
** lemin.h
** File description:
** header of lem-in
*/

#ifndef LEMIN_H_
#define LEMIN_H_

#include <stdlib.h>

typedef struct room_s {
    char *name;
    int ant;
    int pos[2];
    int **way;
    int boolean;
    struct room_s **link;
} room_t;

typedef struct lemin_s {
    room_t *start_room;
    room_t *end_room;
    int nb_ant;
    room_t **tab_room;
    room_t ***ways;
    int nb_ways;
} lemin_t;

room_t *create_room(char **name, char **link);
void create_way(lemin_t *w);
void loop_move(lemin_t *w);
room_t *find_room(room_t *room, char *name, int nb);
void create_way(lemin_t *w);
void loop_move(lemin_t *w);
lemin_t *create_lemin_t(char **input);
char **check_input(void);
int is_alphanum(char c);
int is_room(char *input);
int is_tunnel(char *input);

int my_strlength(char const *str);
char *delete_end(char *str);
char *copy(char *all_buffer, char *buffer);
char *copy_until_n(int i, char **doublearray);
char *cp_until_diez(char *str);

char *first_room(char **darray);
int nb_link(room_t *room);
int nb_room(lemin_t *w);
int my_strcmp_ci(char const *s1, char const *s2);
int my_strcmp_ci_end(char const *s1, char const *s2);
char *last_room(char **darray);
char **tab_room(char **tab, int *i, char **arr);
char **tab_tunnel(char **tab, int *i, char **arr);
char **read_all(char **tab, char *all_buffer, char **arr);
int print_bug(char **arr, int id);
int is_room_ci(char *arr);
int is_tunnel_ci(char *arr);

int verify_ants(char *array);

#endif
