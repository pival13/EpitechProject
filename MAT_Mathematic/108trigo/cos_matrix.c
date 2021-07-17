/*
** EPITECH PROJECT, 2019
** cos_matrix
** File description:
** cosinus of the matrix
*/

#include "my_math.h"

double **cos_matrix(double **mat)
{
    double **matrix;
    int size = 0;

    for (; mat[size] != NULL; size++);
    matrix = create_matrix_i(size);
    for (int i = 1; i != 30; i++) {
        matrix = add_matrix(matrix, mult_matrix(div_fact_mat(pow_matrix(mat, i*2), 2*i), pow(-1, i)));   
    }
    return (matrix);
}