/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonGetter
*/

#include "json.h"

enum json_type json_get_type(const json_t *json)
{
    return json != NULL ? json->type : JSON_NONE;
}

bool json_has_key(const json_t *json, const char *key)
{
    return json_get_with_key(json, key) != NULL;
}

size_t json_get_list_size(const json_t *json)
{
    size_t i = 0;

    if (!json || json->type != JSON_LIST)
        return 0;
    while (json->prev)
        json = json->prev;
    while (json && json->list_value) {
        json = json->next;
        i++;
    }
    return i;
}

char **json_get_all_keys(const json_t *json)
{
    char **tbl;
    size_t size = 0;

    if (!json || json->type != JSON_DICT)
        return NULL;
    while (json->prev)
        json = json->prev;
    for (const json_t *tmp = json; tmp && tmp->dict_value; tmp = tmp->next)
        ++size;
    tbl = malloc(sizeof(char *) * (size+1));
    tbl[size] = NULL;
    for (size_t i = 0; json && json->dict_value; ++i) {
        tbl[i] = strdup(json->key);
        json = json->next;
    }
    return tbl;
}
