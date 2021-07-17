/*
** EPITECH PROJECT, 2019
** my_ls.h
** File description:
** header of my_ls
*/

#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifndef MY_LS_H_
#define MY_LS_H_

#ifndef MOD
#define MOD(x) ((x % 2 == 0) ? ('-') : ('x'))
#endif

#ifndef MODT
#define MODT(x) ((x % 2 == 0) ? ('-') : (((x % 4096 / 512) % 2 == 0) ? \
('x') : ('t')))
#endif

typedef struct list_s {
    char *file;
    struct stat s;
    char *filepath;
} list_t;

int find_nb_file(char *filepath);
void display_content(char *str, long long opt);
char *my_merge(char *s1, char *s2, char *s3);
list_t *my_sort_list_stat(list_t *list);
list_t *my_sort_list_rev(list_t *list);
list_t *my_sort_list_time(list_t *list);
int check_file(char *str);
void write_detail(list_t list, long long opt);

#endif
