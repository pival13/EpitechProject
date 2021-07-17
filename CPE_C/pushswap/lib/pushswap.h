/*
** EPITECH PROJECT, 2018
** pushswap.h
** File description:
** header of pushwap
*/

typedef struct chain_list {
    int nb;
    struct chain_list *next;
    struct chain_list *prev;
} list_t;

void swap(list_t **list);
void rotate(list_t **list);
void rrotate(list_t **list);
void push(list_t **lista, list_t **listb);
void pa(list_t **lista, list_t **listb, int opt);
void pb(list_t **lista, list_t **listb, int opt);
void sa(list_t **list, list_t **listb, int opt);
void ra(list_t **list, list_t **listb, int opt);
void rra(list_t **list, list_t **listb, int opt);
int check_list(list_t *list);
int check_list_pos(list_t *list);
list_t *find_smallest_nb(list_t *list);
int find_nb_rotate(list_t *list, list_t *base);
int find_size(list_t *list);
int find_position(list_t *list);
void print(list_t **list);
void free_list(list_t *list);
list_t *prepare_list(int n, char **num);
void pushswap(list_t **list, int opt);
