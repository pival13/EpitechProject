/*
** EPITECH PROJECT, 2018
** my.h
** File description:
** include
*/

#ifndef MY_H_
#define MY_H_

int my_getnbr(char *str);
int my_str_isnum(char *str);
int my_strlen(char *str);
int **mult_matrice(int **matrice1, int **matrice2);
int **mult_matrice_f(int **matrice1, float **matrice2);
int **create_key(char *ckey);
int **create_str(char *cstr, int **str);
int **create_matrix(char *cstr, int **key);
void crypt(char *cstr, char *ckey);
void decrypt(char *cstr, char *ckey);
float **matrice_invers(int **key);

#endif
