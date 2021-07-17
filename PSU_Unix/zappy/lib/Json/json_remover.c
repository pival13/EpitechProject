/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonRemover
*/

#include "json.h"

static void json_remove_cell_carefully(json_t *json)
{
    json_t *tmp = NULL;

    if (json->key)
        free(json->key);
    free_json(json->list_value);
    if (json->next) {
        tmp = json->next;
        json->next = tmp->next;
        if (json->next)
            json->next->prev = json;
    } else if (json->prev) {
        tmp = json->prev;
        json->prev = tmp->prev;
        if (json->prev)
            json->prev->next = json;
    }
    json->key = tmp != NULL ? tmp->key : NULL;
    json->list_value = tmp != NULL ? tmp->list_value : NULL;
    if (tmp)
        free(tmp);
}

bool json_remove_key(json_t *json, const char *key)
{
    if (!json || json->type != JSON_DICT)
        return false;
    if (!json_has_key(json, key))
        return true;
    if (strcmp(json->key, key)) {
        while (json->prev)
            json = json->prev;
        while (strcmp(json->key, key))
            json = json->next;
        if (json->prev)
            json->prev->next = json->next;
        if (json->next)
            json->next->prev = json->prev;
        free(json->key);
        free_json(json->dict_value);
        free(json);
    } else
        json_remove_cell_carefully(json);
    return true;
}

bool json_remove_value_at_index(json_t *json, size_t index)
{
    json_t *tmp = json;

    if (!json || index >= json_get_list_size(json))
        return false;
    while (json->prev)
        json = json->prev;
    for (size_t i = 0; i != index; i++)
        json = json->next;
    if (json != tmp) {
        if (json->prev)
            json->prev->next = json->next;
        if (json->next)
            json->next->prev = json->prev;
        free(json->list_value);
        free(json);
    } else
        json_remove_cell_carefully(json);
    return true;
}

bool json_remove_value_at_end(json_t *json)
{
    size_t size = json_get_list_size(json);
    return size > 0 && json_remove_value_at_index(json, size-1);
}
