/*
** EPITECH PROJECT, 2019
** add_matrix
** File description:
** add two matrix together
*/

#include "my_math.h"

double **add_matrix(double **mat1, double **mat2)
{
    int size = 0;
    double **matrix;

    for (; mat1[size] != NULL; size++);
    matrix = malloc(sizeof(double *) * (size+1));
    for (int i = 0; i != size; i++)
        matrix[i] = malloc(sizeof(double) * (size));
    matrix[size] = NULL;
    for (int i = 0; i != size; i++)
        for (int j = 0; j != size; j++)
            matrix[i][j] = mat1[i][j] + mat2[i][j];
    return (matrix);
}

double **sub_matrix(double **mat1, double **mat2)
{
    int size = 0;
    double **matrix;

    for (; mat1[size] != NULL; size++);
    matrix = malloc(sizeof(double *) * (size+1));
    for (int i = 0; i != size; i++)
        matrix[i] = malloc(sizeof(double) * (size));
    matrix[size] = NULL;
    for (int i = 0; i != size; i++)
        for (int j = 0; j != size; j++)
            matrix[i][j] = mat1[i][j] - mat2[i][j];
    return (matrix);
}