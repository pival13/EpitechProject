/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** my.h
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "op.h"
#include "vm.h"

#ifndef MY_H
#define MY_H

char ***cut_file(char *filepath);
char **read_file(char *filepath);
char **get_words(char *str);
char *my_strcpy_not_unsigned(char const *src);
char *get_next_line(int fd);
unsigned char *my_strcpy(unsigned char *cpy);
int my_getnbr(char *str);
int is_int(char *str);
int my_strlen(char *arr);
int my_arrlen(char **arr);
int my_strcmp(char *, char *);
int my_strncmp(const char *s1, const char *s2, int n);
int my_strcmp2(char *str, char *str2);
int get_type(int size, int nb);
void my_printf(char *, ...);
void my_dprintf(int fd, char *str, ...);
int my_writer(int fd, char *str, int size);
void *my_memset(void *s, int c, size_t len);

#endif
