/*
** EPITECH PROJECT, 2019
** ln_matrix
** File description:
** logarithme naturel of the matrix
*/

#include "my_math.h"

double **ln_matrix(double **mat)
{
    double **matrix;
    int size = 0;
    double **unity;
    double **y; 

    for (; mat[size] != NULL; size++);
    unity = create_matrix_i(size);
    y = div_2_matrix(sub_matrix(mat, unity), add_matrix(mat, unity));
    matrix = y;
    for (int i = 1; i != 100; i++) {
        matrix = add_matrix(matrix, div_matrix(pow_matrix(y, 2*i+1), 2*i+1));
    }
    matrix = mult_matrix(matrix, 2);
    return (matrix);
}