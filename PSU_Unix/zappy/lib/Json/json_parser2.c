/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonParser
*/

#include "json.h"

void parse_none(const char **s, json_t *json)
{
    json->type = JSON_NONE;
    *s += !strncasecmp(*s, "nil", 3) ? 3 : 4;
}

void parse_bool(const char **s, json_t *json)
{
    json->type = JSON_BOOL;
    json->bool_value = strncasecmp(*s, "true", 4) == 0;
    *s += json->bool_value ? 4 : 5;
}

void parse_number(const char **s, json_t *json)
{
    json->type = JSON_NUMBER;
    json->int_value = strtold(*s, NULL);
    *s += strspn(*s, "0123456789");
    if (**s == '.')
        *s += 1 + strspn(*s+1, "0123456789");
}

void parse_string(const char **s, json_t *json)
{
    json->type = JSON_STRING;
    json->string_value = json_read_string(*s);
    *s += strlen(json->string_value) + 2;
}
