/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** includes
*/

#ifndef MY_H
#define MY_H

int my_strlen(char *str);
double my_getdouble(char *toconvert);

int count_numbers(char *str);
double *numbers_per_line(char *str);
void print_double_tab(double **vars);
int error_management(int ac, char **av);
int *measure_vars(double **vars);

#endif
