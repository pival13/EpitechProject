/*
** EPITECH PROJECT, 2020
** string.h
** File description:
** header of string module
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef MY_STRING_H
#define MY_STRING_H

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
    size_t (*copy)(const struct string_s *, char *, size_t, size_t);
    const char *(*c_str)(const struct string_s *);
    int (*empty)(const struct string_s *);
    int (*find_s)(const struct string_s *, const struct string_s *, size_t);
    int (*find_c)(const struct string_s *, const char *, size_t);
    void (*insert_c)(struct string_s *, size_t, const char *);
    void (*insert_s)(struct string_s *, size_t, const struct string_s *);
    int (*to_int)(const struct string_s *);
    struct string_s **(*split_s)(const struct string_s *, char );
    char **(*split_c)(const struct string_s *, char );
    void (*print)(const struct string_s *);
    void (*join_c)(struct string_s *, char , const char *const *);
    void (*join_s)(struct string_s *, char , const struct string_s *const *);
    struct string_s *(*substr)(const struct string_s *, int , int );
} string_t;

void string_init(string_t *, const char *);
void string_destroy(string_t *);
void assign_s(string_t *, const string_t *);
void assign_c(string_t *, const char *);
void append_s(string_t *, const string_t *);
void append_c(string_t *, const char *);
char at(const string_t *, size_t);
void clear(string_t *);
int size(const string_t *);
int compare_s(const string_t *, const string_t *);
int compare_c(const string_t *, const char *);
size_t copy(const string_t *, char *, size_t, size_t);
const char *c_str(const string_t *);
int empty(const string_t *);
int find_s(const string_t *, const string_t *, size_t);
int find_c(const string_t *, const char *, size_t);
void insert_c(string_t *, size_t, const char *);
void insert_s(string_t *, size_t, const string_t *);
int to_int(const string_t *);
string_t **split_s(const string_t *, char );
char **split_c(const string_t *, char );
void print(const string_t *);
void join_c(string_t *, char , const char *const *);
void join_s(string_t *, char , const string_t *const *);
string_t *substr(const string_t *, int , int );

#endif