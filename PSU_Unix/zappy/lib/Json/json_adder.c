/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonAdder
*/

#include "json.h"

bool json_add_key(json_t *json, const char *key)
{
    if (!json || (json->type != JSON_NONE && json->type != JSON_DICT) ||
        json_has_key(json, key))
        return false;
    return json_add_key_value(json, key, new_json());
}

bool json_add_key_value(json_t *json, const char *key, json_t *value)
{
    if (!json || (json->type != JSON_DICT && json->type != JSON_NONE) ||
        json_has_key(json, key))
        return false;
    else if (json->type == JSON_DICT && json->dict_value != NULL) {
        while (json->next)
            json = json->next;
        json->next = new_json();
        json->next->prev = json;
        json = json->next;
    }
    json->type = JSON_DICT;
    json->key = strdup(key);
    json->dict_value = value != NULL ? value : new_json();
    return true;
}

bool json_add_value_at_index(json_t *json, size_t index, json_t *value)
{
    json_t *tmp;

    if (!json || index > json_get_list_size(json))
        return false;
    else if (index == json_get_list_size(json))
        return json_add_value_at_end(json, value);
    while (json->prev)
        json = json->prev;
    for (size_t i = 0; i != index; i++)
        json = json->next;
    tmp = new_json();
    tmp->list_value = value != NULL ? value : new_json();
    tmp->next = json;
    tmp->prev = json->prev;
    if (json->prev)
        json->prev->next = tmp;
    json->prev = tmp;
    return true;
}

bool json_add_value_at_end(json_t *json, json_t *value)
{
    if (!json || (json->type != JSON_NONE && json->type != JSON_LIST))
        return false;
    else if (json->type == JSON_LIST && json->list_value != NULL) {
        while (json->next)
            json = json->next;
        json->next = new_json();
        json->next->prev = json;
        json = json->next;
    }
    json->type = JSON_LIST;
    json->list_value = value != NULL ? value : new_json();
    return true;
}