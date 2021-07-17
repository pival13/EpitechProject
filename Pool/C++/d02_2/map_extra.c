/*
** EPITECH PROJECT, 2020
** map_extra
** File description:
** extra functions for map
*/

#include "map.h"
#include <stdlib.h>

key_comparator_t key_cmp_container(bool store, key_comparator_t new_key_cmp)
{
    static key_comparator_t cmp;

    if (store)
        cmp = new_key_cmp;
    return cmp;
}

int pair_comparator(void *first, void *second)
{
    key_comparator_t cmp = key_cmp_container(false, NULL);
    return cmp(((pair_t *)first)->key, ((pair_t *)second)->key);
}