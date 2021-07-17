/*
** EPITECH PROJECT, 2020
** string.h
** File description:
** header of string module
*/

#ifndef STRING_H
#define STRING_H

#include <stdlib.h>

typedef struct string_s {
    char *str;
    void (*assign_s)(struct string_s *, const struct string_s *);
    void (*assign_c)(struct string_s *, const char *);
    void (*append_s)(struct string_s *, const struct string_s *);
    void (*append_c)(struct string_s *, const char *);
    char (*at)(const struct string_s *, size_t);
    void (*clear)(struct string_s *);
    int (*size)(const struct string_s *);
    int (*compare_s)(const struct string_s *, const struct string_s *);
    int (*compare_c)(const struct string_s *, const char *);
    size_t (*copy)(const struct string_s *, char *, size_t n, size_t pos);
    const char *(*c_str)(const struct string_s *);
    int (*empty)(const struct string_s *);
    int (*find_s)(const struct string_s *, const struct string_s *, size_t);
    int (*find_c)(const struct string_s *, const char *, size_t pos);
    void (*insert_c)(struct string_s *, size_t pos, const char *);
    void (*insert_s)(struct string_s *, size_t pos, const struct string_s *);
    int (*to_int)(const struct string_s *);
    struct string_s **(*split_s)(const struct string_s *, char delim);
    char **(*split_c)(const struct string_s *, char delim);
    void (*print)(const struct string_s *);
    void (*join_c)(struct string_s *, char delim, const char *const *);
    void (*join_s)(struct string_s *, char, const struct string_s *const *);
    struct string_s *(*substr)(const struct string_s *, int pos, int length);
} string_t;

void string_init(string_t *, const char *);
void string_destroy(string_t *);

#endif