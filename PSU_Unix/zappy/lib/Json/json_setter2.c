/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonSetter
*/

#include "json.h"

void json_set_as_list(json_t *json, json_t *values[])
{
    if (!json)
        return;
    json_set_as_none(json);
    json->type = JSON_LIST;
    json->list_value = NULL;
    for (size_t i = 0; values != NULL && values[i] != NULL; i++)
        json_add_value_at_end(json, values[i]);
}

void json_set_as_dict(json_t *json, const char *keys[], json_t *values[])
{
    if (!json)
        return;
    json_set_as_none(json);
    json->type = JSON_DICT;
    json->dict_value = NULL;
    json->key = NULL;
    for (size_t i = 0; keys != NULL && values != NULL && keys[i] != NULL &&
        values[i] != NULL; i++)
        json_add_key_value(json, keys[i], values[i]);
}

bool json_set_value_at_key(json_t *json, const char *key, json_t *value)
{
    if (!json || !json_has_key(json, key))
        return false;
    while (json->prev)
        json = json->prev;
    while (strcmp(json->key, key))
        json = json->next;
    free_json(json->dict_value);
    json->dict_value = value != NULL ? value : new_json();
    return true;
}

bool json_set_value_at_index(json_t *json, size_t index, json_t *value)
{
    if (!json || index >= json_get_list_size(json))
        return false;
    while (json->prev)
        json = json->prev;
    for (size_t i = 0; i != index; i++)
        json = json->next;
    free_json(json->list_value);
    json->list_value = value != NULL ? value : new_json();
    return true;
}
