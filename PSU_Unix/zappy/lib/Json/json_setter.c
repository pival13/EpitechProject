/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonSetter
*/

#include "json.h"

void json_set_as_none(json_t *json)
{
    if (!json)
        return;
    if (json->type == JSON_LIST)
        json_clean_list(json);
    if (json->type == JSON_DICT)
        json_clean_dict(json);
    if (json->type == JSON_STRING)
        free(json->string_value);
    json->type = JSON_NONE;
}

void json_set_as_bool(json_t *json, bool b)
{
    if (!json)
        return;
    json_set_as_none(json);
    json->type = JSON_BOOL;
    json->bool_value = b;
}

void json_set_as_number(json_t *json, long double nb)
{
    if (!json)
        return;
    json_set_as_none(json);
    json->type = JSON_NUMBER;
    json->int_value = nb;
}

void json_set_as_string_with_free(json_t *json, char *str)
{
    if (!json)
        return;
    json_set_as_none(json);
    json->type = JSON_STRING;
    json->string_value = str;
}

void json_set_as_string(json_t *json, const char *str)
{
    if (!json || !str)
        return;
    json_set_as_string_with_free(json, strdup(str));
}
