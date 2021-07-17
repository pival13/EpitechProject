/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonPrinter
*/

#include "json.h"

static void display_json2(const json_t *json, size_t indent);

static void display_list(const json_t *json, size_t indent)
{
    if (json->list_value == NULL) {
        printf("[]");
        return;
    }
    printf("[\n");
    while (json->prev)
        json = json->prev;
    while (json != NULL && json->list_value != NULL) {
        for (size_t i = 0; i != indent+JSON_INDENT; i++)
            printf(" ");
        display_json2(json->list_value, indent+JSON_INDENT);
        json = json->next;
        if (json)
            printf(",\n");
    }
    printf("\n");
    for (size_t i = 0; i != indent; i++)
        printf(" ");
    printf("]");
}

static void display_dict(const json_t *json, size_t indent)
{
    if (json->dict_value == NULL) {
        printf("{}");
        return;
    }
    printf("{\n");
    while (json->prev)
        json = json->prev;
    while (json != NULL) {
        for (size_t i = 0; i != indent+JSON_INDENT; i++)
            printf(" ");
        printf("\"%s\": ", json->key);
        display_json2(json->dict_value, indent+JSON_INDENT);
        json = json->next;
        if (json)
            printf(",\n");
    }
    printf("\n");
    for (size_t i = 0; i != indent; i++)
        printf(" ");
    printf("}");
}

static void display_json2(const json_t *json, size_t indent)
{
    switch (json->type) {
        case JSON_NONE:
            printf("null");
            break;
        case JSON_BOOL:
            printf(json->bool_value ? "true": "false");
            break;
        case JSON_NUMBER:
            printf("%Lg", json->int_value);
            break;
        case JSON_STRING:
            printf("\"%s\"", json->string_value);
            break;
        case JSON_LIST:
            display_list(json, indent);
            break;
        case JSON_DICT:
            display_dict(json, indent);
            break;
    }
}

void display_json(const json_t *json)
{
    if (!json)
        return;
    display_json2(json, 0);
    printf("\n");
}