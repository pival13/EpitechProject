/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** header for libs
*/

#ifndef MY_LIB_H
#define MY_LIB_H

int my_arraylen(char **str);
char ***cut_file_char(char *filepath, char c);
char *load_file_in_mem(char *filepath);
void clean_str(char *str);
void clean_array(char **array);
void free_tab(char **tab);
void free_tab3(char ***tab);
char *get_next_line(int fd);
char **get_words(char const *str);
int has_word(char *str, char *word);
int is_float(char const *str);
int is_int(char const *str);
int is_letter(char const *str);
int my_getnbr(char const *str);
char *my_getword(char const *str);
int my_getnbr_base(char const *str, char const *base);
int my_is_prime(int nb);
void my_dprintf(int fd, const char *str, ...);
char *my_merge_3(char *s1, char *s2, char *s3);
int my_put_nbr(int nb);
int my_putnbr_base(int nbr, char const *base);
int my_putstr(char const *str);
void my_sort_int_array(int *array, int size);
void my_sort_list(char **array);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
int my_strcmp_full(char const *s1, char const *s2);
int my_strcmp_maj(char const *s1, char const *s2);
char *my_strcpy(char *src);
char *my_strdup(char const *src);
int my_strlen(char const *str);
char *my_strncat(char *dest, char const *src, int nb);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strstr(char *str, char const *to_find);
int nb_row(char **arr);
char **read_file(char *filepath);
char ***cut_file(char *filepath);
char *str_add(char *s, char *s2);
char *my_atoi(int nb);
char *my_revstr(char *s);
char *create_string(int size);
char **create_tab(int size);

#endif
