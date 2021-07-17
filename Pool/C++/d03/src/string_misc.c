/*
** EPITECH PROJECT, 2020
** string.c
** File description:
** initial functions for string
*/

#include "my_string.h"
#include <unistd.h>

char at(const string_t *this, size_t pos)
{
    if (this == NULL || this->str == NULL || pos >= strlen(this->str))
        return -1;
    return this->str[pos];
}

int size(const string_t *this)
{
    if (this == NULL || this->str == NULL)
        return -1;
    return strlen(this->str);
}

int empty(const string_t *this)
{
    if (this == NULL || this->str == NULL || size(this) == 0)
        return 1;
    return 0;
}

void clear(string_t *this)
{
    if (this == NULL)
        return;
    string_destroy(this);
    string_init(this, "");
}

void print(const string_t *this)
{
    if (this == NULL || this->str == NULL)
        return;
    write(1, this->str, size(this));
}