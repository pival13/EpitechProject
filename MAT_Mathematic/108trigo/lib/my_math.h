/*
** EPITECH PROJECT, 2019
** math.h
** File description:
** header of math.h
*/

#include <math.h>
#include <stdlib.h>

long long factoriel(int nb);
double **div_matrix(double **matrix, long long nb);
double **mult_matrix(double **matrix, double nb);
double **mult_2_matrix(double **mat1, double **mat2);
double **add_matrix(double **mat1, double **mat2);
double **sub_matrix(double **mat1, double **mat2);
double **create_matrix(char **arg, int size);
double **copy_matrix(double **mat);
double **create_matrix_i(int size);
int is_float(char const *str);
double **pow_matrix(double **mat1, int pow);
double **div_fact_mat(double **mat, int fact);
double **inv_matrix(double **key);
double **div_2_matrix(double **mat1, double **mat2);
double **exp_matrix(double **mat);
double **ln_matrix(double **mat);
double **sin_matrix(double **mat);
double **sinh_matrix(double **mat);
double **cos_matrix(double **mat);
double **cosh_matrix(double **mat);
double **tan_matrix(double **mat);