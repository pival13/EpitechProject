/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonGetter
*/

#include "json.h"

bool json_get_bool(const json_t *json)
{
    return json && json->type == JSON_BOOL ? json->bool_value : false;
}

long double json_get_number(const json_t *json)
{
    return json && json->type == JSON_NUMBER ? json->int_value : 0;
}

const char *json_get_string(const json_t *json)
{
    return json && json->type == JSON_STRING ? json->string_value : NULL;
}

json_t *json_get_at_index(const json_t *json, size_t index)
{
    if (!json || json->type != JSON_LIST)
        return NULL;
    while (json->prev)
        json = json->prev;
    for (size_t i = 0; i < index && json; i++)
        json = json->next;
    return json != NULL ? json->list_value : NULL;
}

json_t *json_get_with_key(const json_t *json, const char *key)
{
    if (!json || json->type != JSON_DICT)
        return NULL;
    while (json->prev)
        json = json->prev;
    while (json)
        if (json->key && key && !strcmp(json->key, key))
            return json->dict_value;
        else if (!key && !json->key)
            return json->dict_value;
        else
            json = json->next;
    return NULL;
}