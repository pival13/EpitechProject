/*
** EPITECH PROJECT, 2020
** string.c
** File description:
** initial functions for string
*/

#include "my_string.h"

size_t copy(const string_t *this, char *s, size_t n, size_t pos)
{
    size_t i = 0;

    if (this == NULL || s == NULL || this->str == NULL)
        return 0;
    if (pos >= strlen(this->str))
        return 0;
    for (; i != n && this->str[i+pos] != '\0'; i++)
        s[i] = this->str[i+pos];
    if (i != n) {
        s[i] = '\0';
        i++;
    }
    return i;
}

const char *c_str(const string_t *this)
{
    if (this == NULL)
        return NULL;
    return this->str;
}

int to_int(const string_t *this)
{
    if (this == NULL || this->str == NULL)
        return 0;
    return atoi(this->str);
}

void join_c(string_t *this, char delim, const char *const *tab)
{
    if (this == NULL || tab == NULL)
        return;
    assign_c(this, tab[0]);
    for (size_t i = 1; tab[i] != NULL; i++) {
        append_c(this, (char[2]){delim, '\0'});
        append_c(this, tab[i]);
    }
}

void join_s(string_t *this, char delim, const string_t *const *tab)
{
    if (this == NULL || tab == NULL || tab[0] == NULL)
        return;
    assign_s(this, tab[0]);
    for (size_t i = 1; tab[i] != NULL; i++) {
        append_c(this, (char[2]){delim, '\0'});
        append_s(this, tab[i]);
    }
}