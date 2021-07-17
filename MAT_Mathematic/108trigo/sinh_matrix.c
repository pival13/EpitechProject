/*
** EPITECH PROJECT, 2019
** sinh_matrix
** File description:
** sinush of the matrix
*/

#include "my_math.h"

double **sinh_matrix(double **mat)
{
    double **matrix = copy_matrix(mat);
    int size = 0;

    for (; mat[size] != NULL; size++);
    for (int i = 1; i != 30; i++) {
        matrix = add_matrix(matrix, div_fact_mat(pow_matrix(mat, i*2+1), 2*i+1));
    }
    return (matrix);
}