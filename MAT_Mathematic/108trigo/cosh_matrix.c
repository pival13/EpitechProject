/*
** EPITECH PROJECT, 2019
** cosh_matrix
** File description:
** cosinush of the matrix
*/

#include "my_math.h"

double **cosh_matrix(double **mat)
{
    double **matrix;
    int size = 0;

    for (; mat[size] != NULL; size++);
    matrix = create_matrix_i(size);
    for (int i = 1; i != 30; i++) {
        matrix = add_matrix(matrix, div_fact_mat(pow_matrix(mat, i*2), 2*i));
        //printf("%f %lld\n", pow(-1, i), factoriel(2*i+1));
    }
    return (matrix);
}