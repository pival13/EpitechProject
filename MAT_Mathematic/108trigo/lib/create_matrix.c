/*
** EPITECH PROJECT, 2019
** create_matrix
** File description:
** create a matrix
*/

#include "my_math.h"

double **create_matrix(char **arg, int size)
{
    double **matrix;

    matrix = malloc(sizeof(double *) * (size+1));
    for (int i = 0; i != size; i++)
        matrix[i] = malloc(sizeof(double) * (size));
    matrix[size] = NULL;
    for (int i = 0; i != size; i++)
        for (int j = 0; j != size; j++)
            matrix[i][j] = atof(arg[i*size+j]);
    return (matrix);
}

double **copy_matrix(double **mat)
{
    double **matrix;
    int size = 0;

    for (; mat[size] != NULL; size++);
    matrix = malloc(sizeof(double *) * (size+1));
    for (int i = 0; i != size; i++)
        matrix[i] = malloc(sizeof(double) * (size));
    matrix[size] = NULL;
    for (int i = 0; i != size; i++)
        for (int j = 0; j != size; j++)
            matrix[i][j] = mat[i][j];
    return (matrix);
}

double **create_matrix_i(int size)
{
    double **matrix = malloc(sizeof(double *) * (size+1));
    for (int i = 0; i != size; i++)
        matrix[i] = malloc(sizeof(double) * (size));
    matrix[size] = NULL;
    for (int i = 0; i != size; i++)
        for (int j = 0; j != size; j++)
            if (i == j)
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;
    return (matrix);
}