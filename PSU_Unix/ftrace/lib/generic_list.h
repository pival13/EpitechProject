/*
** EPITECH PROJECT, 2018
** cpp_d02a
** File description:
** ex02
*/

#ifndef GENERIC_LIST_H_
#define GENERIC_LIST_H_

#include <stdbool.h>
#include <stdlib.h>

/***********************/
/*        List         */
/***********************/

typedef struct node
{
    void        *value;
    struct node *next;
} node_t;

typedef node_t *list_t;

typedef void (*value_displayer_t)(void *value);
typedef int (*value_comparator_t)(void *first, void *second);

size_t list_size(list_t list);
bool list_empty(list_t list);
void list_dump(list_t list, value_displayer_t val_disp);
void list_clear(list_t *front_ptr);
void list_sort(list_t front_ptr, value_comparator_t comp);

bool list_push_front(list_t *front_ptr, void *elem);
bool list_push_back(list_t *front_ptr, void *elem);
bool list_push(list_t *front_ptr, void *elem, size_t position);
bool list_pop_front(list_t *front_ptr);
bool list_pop_back(list_t *front_ptr);
bool list_pop(list_t *front_ptr, size_t position);

void *list_get_front(list_t list);
void *list_get_back(list_t list);
void *list_get(list_t list, size_t position);

bool list_del_node(list_t *front_ptr, node_t *node_ptr);
node_t *list_get_first_node_with_value(list_t list, void *value,
    value_comparator_t val_comp);

/***********************/
/*         Map         */
/***********************/

typedef struct pair
{
    void    *key;
    void    *value;
}   pair_t;

typedef list_t map_t;

typedef int (*key_comparator_t)(void *first_key, void *second_key);

size_t map_size(map_t map);
bool map_empty(map_t map);

key_comparator_t key_cmp_container(bool store, key_comparator_t new_key_cmp);
int pair_comparator(void *first, void *second);

bool map_add(map_t *map_ptr, void *key, void *value, key_comparator_t key_cmp);
bool map_del(map_t *map_ptr, void *key, key_comparator_t key_cmp);

void *map_get(map_t map, void *key, key_comparator_t key_cmp);

#endif /* !GENERIC_LIST_H_ */
