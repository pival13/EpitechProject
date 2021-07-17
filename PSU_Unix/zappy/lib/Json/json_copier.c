/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonCopier
*/

#include "json.h"

static json_t *json_copy_list_json(json_t *dest, const json_t *src, 
    bool copy_key)
{
    dest->type = copy_key ? JSON_DICT : JSON_LIST;
    if (copy_key && src->key)
        dest->key = strdup(src->key);
    else if (copy_key)
        dest->key = NULL;
    if (src->list_value != NULL)
        dest->list_value = json_copy_new_json(src->list_value);
    else
        dest->list_value = NULL;
    if (src->next) {
        dest->next = new_json();
        dest->next = json_copy_list_json(dest->next, src->next, copy_key);
        dest->next->prev = dest;
    }
    return dest;
}

json_t *json_copy_new_json(const json_t *json)
{
    if (!json)
        return NULL;
    return json_copy(new_json(), json);
}

json_t *json_copy(json_t *dest, const json_t *src)
{
    if (!src || !dest)
        return NULL;
    json_set_as_none(dest);
    while (src->prev)
        src = src->prev;
    
    if (src->type == JSON_BOOL)
        json_set_as_bool(dest, src->bool_value);
    if (src->type == JSON_NUMBER)
        json_set_as_number(dest, src->int_value);
    if (src->type == JSON_STRING)
        json_set_as_string(dest, src->string_value);
    if (src->type == JSON_DICT)
        json_copy_list_json(dest, src, true);
    if (src->type == JSON_LIST)
        json_copy_list_json(dest, src, false);
    return dest;
}

json_t *json_move(json_t *dest, const json_t *src)
{
    if (!src || !dest)
        return NULL;
    json_set_as_none(dest);
    memmove(dest, src, sizeof(json_t));
    return dest;
}