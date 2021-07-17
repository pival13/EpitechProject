/*
** EPITECH PROJECT, 2019
** 
** File description:
** make a matrix to a power
*/

#include "my_math.h"

double **pow_matrix(double **mat1, int pow)
{
    int size = 0;
    double **matrix;

    for (; mat1[size] != NULL; size++);
    if (pow == 0)
        return (create_matrix_i(size));
    matrix = copy_matrix(mat1);
    for (int i = 1; i != pow; i++)
        matrix = mult_2_matrix(matrix, mat1);
    return (matrix);
}
