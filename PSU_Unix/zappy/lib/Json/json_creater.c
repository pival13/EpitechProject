/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonCreater
*/

#include "json.h"

json_t *new_json()
{
    json_t *json = (json_t *)malloc(sizeof(json_t));
    memset(json, 0, sizeof(json_t));
    json->type = JSON_NONE;
    return json;
}

json_t *new_json_as_bool(bool b)
{
    json_t *json = new_json();
    json_set_as_bool(json, b);
    return json;
}

json_t *new_json_as_number(long double nb)
{
    json_t *json = new_json();
    json_set_as_number(json, nb);
    return json;
}

json_t *new_json_as_string(const char *s)
{
    json_t *json = new_json();
    json_set_as_string(json, s);
    return json;
}

json_t *new_json_as_string_with_free(char *s)
{
    json_t *json = new_json();
    json_set_as_string_with_free(json, s);
    return json;
}
