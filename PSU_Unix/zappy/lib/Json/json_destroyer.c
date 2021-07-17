/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonDestroyer
*/

#include "json.h"

bool json_clean_list(json_t *json)
{
    if (json->type != JSON_LIST && json->type != JSON_NONE)
        return false;
    while (json->type == JSON_LIST && json->list_value != NULL)
        json_remove_value_at_index(json, 0);
    return true;
}

bool json_clean_dict(json_t *json)
{
    if (json->type != JSON_DICT && json->type != JSON_NONE)
        return false;
    while (json->type == JSON_DICT && json->dict_value != NULL)
        json_remove_key(json, json->key);
    return true;
}

static void free_json_cell(json_t *json)
{
    if (json->type == JSON_LIST)
        free_json(json->list_value);
    if (json->type == JSON_STRING && json->string_value)
        free(json->string_value);
    if (json->type == JSON_DICT) {
        if (json->key)
            free(json->key);
        free_json(json->dict_value);
    }
    free(json);
}

void free_json(json_t *json)
{
    json_t *tmp;

    if (!json)
        return;
    while (json->prev != NULL)
        json = json->prev;
    while (json->next != NULL) {
        tmp = json->next;
        json->next = tmp->next;
        free_json_cell(tmp);
    }
    free_json_cell(json);
}