/*
** EPITECH PROJECT, 2020
** string.c
** File description:
** initial functions for string
*/

#include "my_string.h"

void append_c(string_t *this, const char *ap)
{
    char *s;

    if (this == NULL || ap == NULL)
        return;
    if (this->str == NULL)
        return assign_c(this, ap);
    s = malloc(sizeof(char) * (strlen(this->str) + strlen(ap) + 1));
    s[0] = '\0';
    if (s == NULL)
        return;
    s = strcat(s, this->str);
    s = strcat(s, ap);
    free(this->str);
    this->str = s;
}

void append_s(string_t *this, const string_t *ap)
{
    if (ap != NULL)
        append_c(this, ap->str);
}

void insert_c(string_t *this, size_t pos, const char *str)
{
    char *tmp;

    if (this == NULL || this->str == NULL || str == NULL)
        return;
    if (pos > strlen(this->str))
        return append_c(this, str);
    tmp = this->str;
    this->str = malloc(sizeof(char) * (strlen(tmp) + strlen(str) + 1));
    if (this->str == NULL)
        return;
    for (size_t i = 0; i < strlen(tmp) + strlen(str); i++)
        if (i < pos)
            this->str[i] = tmp[i];
        else if (i >= pos + strlen(str))
            this->str[i] = tmp[i-strlen(str)];
        else
            this->str[i] = str[i-pos];
    this->str[strlen(tmp) + strlen(str)] = '\0';
    free(tmp);
}

void insert_s(string_t *this, size_t pos, const string_t *str)
{
    if (str != NULL)
        insert_c(this, pos, str->str);
}
