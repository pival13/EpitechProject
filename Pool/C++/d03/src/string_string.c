/*
** EPITECH PROJECT, 2020
** string.c
** File description:
** initial functions for string
*/

#include "my_string.h"

int find_c(const string_t *this, const char *str, size_t pos)
{
    char *s;

    if (this == NULL || this->str == NULL || str == NULL)
        return -1;
    if (pos > strlen(this->str))
        return -1;
    s = strstr(&this->str[pos], str);
    if (s == NULL)
        return -1;
    return s - this->str;
}

int find_s(const string_t *this, const string_t *str, size_t pos)
{
    if (str != NULL)
        return find_c(this, str->str, pos);
    return -1;
}

int compare_c(const string_t *this, const char *str)
{
    if (this == NULL)
        return 0;
    if (this->str == NULL && str == NULL)
        return 0;
    if (this->str == NULL)
        return strcmp("", str);
    if (str == NULL)
        return strcmp(this->str, "");
    return strcmp(this->str, str);
}

int compare_s(const string_t *this, const string_t *str)
{
    if (str != NULL)
        return compare_c(this, str->str);
    return 0;
}