/*
** EPITECH PROJECT, 2019
** exp_matrix
** File description:
** calcul the exponentiel of the matrix
*/

#include "my_math.h"

double **exp_matrix(double **mat)
{
    int size = 0;
    double **matrix;

    for (; mat[size] != NULL; size++);
    matrix = create_matrix_i(size);
    for (int i = 1; i != 50; i++) {
        matrix = add_matrix(matrix, div_fact_mat(pow_matrix(mat, i), i));
    }
    return (matrix);
}
