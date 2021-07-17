/*
** EPITECH PROJECT, 2018
** my.h
** File description:
** Useful to call functions
*/

#ifndef MY_H
#define MY_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int my_getnbr(char *);

float my_getfloat2(char *toconvert, int point_pos, float number, int mult);

float my_getfloat(char *toconvert);

char *str_add(char *, char *);

char *my_erasestr(char *str);

int my_compute_square_root(int nb);

char *my_get_strtonbr(int nbr);

int my_is_prime(int nb);

void my_putchar(char c);

int my_put_nbr(int nb);

int my_putnbr_base(int nbr, char const *base);

int my_putstr(char const *str);

char *my_revstr(char *str);

int my_showmem(char const *str);

int my_showstr(char const *str);

int my_sort_int_array(char const *str);

int my_strcmp(char const *s1, char const *s2);

char *my_strcpy(char *dest, char const *src);

int my_str_islower(char const *str);

int my_str_isnum(char const *str);

int my_str_isprintable(char const *str);

int my_str_isupper(char const *str);

int my_strlen(char const *str);

char *my_strlowcase(char *str);

int my_strncmp(char const *s1, char const *s2, int n);

char *my_strncpy(char *dest, char const *src, int n);

char *my_strupcase(char *str);

void my_swap(int *a, int *b);

int my_show_word_array(char * const *tab);

int my_strlen_4(char const *str);

void decimal(int nbr);

int identify(char const *base);

void binary(int nbr);

void hexadecimal(int nbr);

char *my_strstr(char *dest, char const *src);

int alphaornotfunc(char c);

char **mallocarray(char const *str, char **array);

char **writing(char const *str, char **array, int alphaornot, int j);

char *convert_base(char const *, char const *, char const *);

char *mallocnbrfinal(int nbr, int baseto);

char *convert(int nbr, int baseto, char *nbrfinal);

int comprehension(char *nbr, int basefrom);

int errorfuncbase(char *nbr, int base);

int my_atoi(char const *);

char *eval_expr(char const *str);

typedef struct var_add {
    int length;
    int t1;
    int t2;
    int limit;
    char *nbf;
    char *nb1;
    char *nb2;
} var_add;

typedef struct sV {
    int length;
    int t1;
    int t2;
    int li;
    char *nbf;
    char *nb1;
    char *nb2;
    int rtn;
} sV;

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int check_error(char *av1, char *av2);
char *infin_div(char *av1, char *av2);
int formul(char *av2, char *n, char *av1);
char *sign_division(char *tf1);
char *rewrite(char *nbf);
void calcul_addition(var_add *addV);
char *addition(char *nb1, char *nb2, char *nbf, int opetype);
int checkvaliditymult(char *nb1, char *nb2);
char *signemult(char *number);
int optypemult(char *nb1, char *nb2);
char *operationmult(char *nb1, char *nb2, char *numberfinal, int opetype);
char *infin_mult(char *nb1, char *nb2);
void echangeopetype1(sV *var);
void echangeminus(sV *var);
void superior(sV *var);
void rewriteminus(sV *var);
void calculsoustraction(sV *var);
int checkvalidity(char *nb1, char *nb2);
char *signe(char *number);
int optype(char *nb1, char *nb2);
char *operation(char *nb1, char *nb2, char *numberfinal, int opetype);
char *infin_add(char *nb1, char *nb2);
char *infin_sub(char *nb1, char *nb2);
char *multiplication(char *nb1, char *nb2, int opetype);
char *multiplication2(char nb1, char *nb2);
char *addzero(char *toadd, int digitplus);
char *removeminus(char *nb);
char *addminus(char *nb);
int nbrlength(char *number1, char *number2);
void compteurt1t2(sV *var);
char *soustraction(char *, char *, char *, int);
char *infin_modulo(char *, char *);
char *modulonominus(char *);
char *first_trad_sign2(char *mem, int i, int j);
char *first_trad_sign(char *mem, int i, int j);
char *first_trad(char *base, char *operators, char *expr, int size);
char *last_trad(char *base, char *numeral_result, int size);

#endif
