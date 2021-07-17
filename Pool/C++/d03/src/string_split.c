/*
** EPITECH PROJECT, 2020
** string.c
** File description:
** initial functions for string
*/

#include "my_string.h"

static int nb_char(const char *str, char c)
{
    int i = 0;

    for (size_t j = 0; j < strlen(str); j++)
        if (str[j] == c)
            i++;
    return i;
}

char **split_c(const string_t *this, char separator)
{
    char **arr;
    size_t i = 1;

    if (this == NULL || this->str == NULL)
        return NULL;
    arr = malloc(sizeof(char *) * (nb_char(this->str, separator) + 2));
    if (arr == NULL)
        return NULL;
    arr[0] = strdup(this->str);
    for (size_t j = 0; j < strlen(this->str); j++)
        if (arr[0][j] == separator) {
            arr[0][j] = '\0';
            arr[i] = &arr[0][j+1];
            i++;
        }
    arr[i] = NULL;
    return arr;
}

string_t **split_s(const string_t *this, char separator)
{
    string_t **arr;
    char **ar = split_c(this, separator);

    if (this == NULL || this->str == NULL || ar == NULL)
        return NULL;
    arr = malloc(sizeof(string_t *) * (nb_char(this->str, separator) + 2));
    for (int i = 0; i != nb_char(this->str, separator) + 1; i++) {
        arr[i] = malloc(sizeof(string_t));
        string_init(arr[i], ar[i]);
    }
    arr[nb_char(this->str, separator) + 1] = NULL;
    free(ar[0]);
    free(ar);
    return arr;
}

static void find_index(int *pos, int *length, const size_t len)
{
    if (*pos < 0)
        *pos += len;
    if (*length < 0) {
        *length = -(*length);
        *pos -= *length;
    }
    if (*pos < 0) {
        *length += *pos;
        *pos = 0;
    }
    if (*length < 0)
        *length = 0;
    if (*pos + *length >= (int)len)
        *length = len - *pos;
    if (*length <= 0) {
        *pos = 0;
        *length = 0;
    }
}

string_t *substr(const string_t *this, int offset, int length)
{
    string_t *str;
    char *s;

    if (this == NULL || this->str == NULL)
        return NULL;
    find_index(&offset, &length, strlen(this->str));
    s = strdup(&this->str[offset]);
    s[length] = '\0';
    str = malloc(sizeof(string_t));
    string_init(str, s);
    free(s);
    return str;
}