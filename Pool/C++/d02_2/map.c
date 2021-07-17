/*
** EPITECH PROJECT, 2020
** map
** File description:
** map
*/

#include "map.h"
#include <stdlib.h>

unsigned int map_get_size(map_t map)
{
    return list_get_size(map);
}

bool map_is_empty(map_t map)
{
    return map == NULL;
}

bool map_add_elem(map_t *map_ptr, void *key, void *value,
                    key_comparator_t key_cmp)
{
    pair_t *pair = malloc(sizeof(pair_t));
    map_t map;

    if (pair == NULL)
        return false;
    pair->key = key;
    pair->value = value;
    key_cmp_container(true, key_cmp);
    map = list_get_first_node_with_value(*map_ptr, pair, pair_comparator);
    if (map != NULL) {
        free(pair);
        ((pair_t *)map->value)->value = value;
        return true;
    } else
        return list_add_elem_at_back(map_ptr, pair);
}

bool map_del_elem(map_t *map_ptr, void *key, key_comparator_t key_cmp)
{
    pair_t pair = { .key = key };
    map_t map;

    key_cmp_container(true, key_cmp);
    map = list_get_first_node_with_value(*map_ptr, &pair, pair_comparator);
    free(map->value);
    return list_del_node(map_ptr, map);
}

void *map_get_elem(map_t map, void *key, key_comparator_t key_cmp)
{
    pair_t pair = { .key = key };

    key_cmp_container(true, key_cmp);
    map = list_get_first_node_with_value(map, &pair, pair_comparator);
    if (map != NULL)
        return ((pair_t *)map->value)->value;
    else
        return NULL;
}