/*
** EPITECH PROJECT, 2018
** my.h
** File description:
** Header of mylib
*/

#ifndef MY_H
#define MY_H

char *get_next_line(int fd);
int my_compute_power_rec(int nb, int p);
int my_compute_square_root(int nb);
int my_find_prime_sup(int nb);
int my_getnbr(char const *str);
int my_getnbr_base(char const *str, char const *base);
int my_isneg(int n);
int my_is_prime(int nb);
int my_printf(const char *str, ...);
void my_putchar(char c);
int my_put_nbr(int nb);
int my_putnbr_base(int nbr, char const *base);
void my_putstr(char const *str);
char *my_revstr(char *str);
int my_showmem(char const *str, int size);
int my_showstr(char const *str);
int my_show_word_array(char * const *tab);
void my_sort_int_array(int *array, int size);
void my_sort_list(char **array);
char *my_strcapitalize(char *str);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
int my_strcmp_full(char const *s1, char const *s2);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
int my_str_isalpha(char const *str);
int my_str_islower(char const *str);
int is_int(char const *str);
int my_str_isfloat(char const *str);
int my_str_isprintable(char const *str);
int my_str_isupper(char const *str);
int my_strlen(char const *str);
char *my_strlowcase(char *str);
char *my_strncat(char *dest, char const *src, int nb);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strstr(char *str, char const *to_find);
char **my_str_to_word_array(char const *str);
char *my_strupcase(char *str);
void my_swap(int *a, int *b);
void my_print_array(char **arr);

#endif //_MY_H_
