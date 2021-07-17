/*
** EPITECH PROJECT, 2019
** tan_matrix
** File description:
** tangente of the matrix
*/

#include "my_math.h"

double **tan_matrix(double **mat)
{
    int size = 0;
    double **cosinus = cos_matrix(mat);
    double **matrix = div_2_matrix(mat, cosinus);

    for (; mat[size] != NULL; size++);
    for (int i = 1; i != 50; i++) {
        matrix = add_matrix(matrix, div_2_matrix(mult_matrix(div_fact_mat(pow_matrix(mat, i*2+1), 2*i+1), pow(-1, i)), cosinus));
    }
    return (matrix);
}