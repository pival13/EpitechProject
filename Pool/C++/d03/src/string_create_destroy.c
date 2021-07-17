/*
** EPITECH PROJECT, 2020
** string.c
** File description:
** initial functions for string
*/

#include "my_string.h"

void string_init_next(string_t *s)
{
    s->insert_s = insert_s;
    s->insert_c = insert_c;
    s->to_int = to_int;
    s->split_s = split_s;
    s->split_c = split_c;
    s->print = print;
    s->join_c = join_c;
    s->join_s = join_s;
    s->substr = substr;
}

void string_init(string_t *s, const char *str)
{
    if (s == NULL)
        return;
    s->str = NULL;
    if (str != NULL)
        s->str = strdup(str);
    s->assign_c = assign_c;
    s->assign_s = assign_s;
    s->append_c = append_c;
    s->append_s = append_s;
    s->at = at;
    s->clear = clear;
    s->size = size ;
    s->compare_c = compare_c;
    s->compare_s = compare_s;
    s->copy = copy;
    s->c_str = c_str;
    s->empty = empty;
    s->find_c = find_c;
    s->find_s = find_s;
    string_init_next(s);
}

void string_destroy(string_t *s)
{
    if (s == NULL || s->str == NULL)
        return;
    free(s->str);
    s->str = NULL;
}

void assign_c(string_t *this, const char *s)
{
    char *str;

    if (this == NULL)
        return;
    str = strdup(s);
    string_destroy(this);
    this->str = str;
}

void assign_s(string_t *this, const string_t *str)
{
    if (str != NULL)
        assign_c(this, str->str);
}