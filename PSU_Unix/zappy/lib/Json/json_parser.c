/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonParser
*/

#include "json.h"

void parse_list(const char **s, json_t *json)
{
    json->type = JSON_LIST;
    if (**s != ']') {
        json->list_value = new_json();
        parse_json(s, json->list_value);
        if (**s == ',') {
            *s += 1;
            json->next = new_json();
            json->next->prev = json;
            parse_list(s, json->next);
            *s -= 1;
        }
    } else
        json->list_value = NULL;
    *s += 1;
}

void parse_dict(const char **s, json_t *json)
{
    json->type = JSON_DICT;
    if (**s != '}') {
        json->key = json_read_string(*s);
        *s += 1 + strlen(json->key) + 1 + 1;
        json->dict_value = new_json();
        parse_json(s, json->dict_value);
        if (**s == ',') {
            *s += 1;
            json->next = new_json();
            json->next->prev = json;
            parse_dict(s, json->next);
            *s -= 1;
        }
    } else {
        json->dict_value = NULL;
        json->key = NULL;
    }
    *s += 1;
}

void parse_json(const char **s, json_t *json)
{
    if (**s == '[') {
        *s += 1;
        parse_list(s, json);
    }
    if (**s == '{') {
        *s += 1;
        parse_dict(s, json);
    }
    if (isdigit(**s))
        parse_number(s, json);
    if (**s == '"')
        parse_string(s, json);
    if (!strncasecmp(*s, "true", 4) || !strncasecmp(*s, "false", 5))
        parse_bool(s, json);
    if (!strncasecmp(*s, "none", 4) || !strncasecmp(*s, "null", 4) ||
        !strncasecmp(*s, "nil", 4))
        parse_none(s, json);
}
