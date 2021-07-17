/*
** EPITECH PROJECT, 2019
** mult_matrice
** File description:
** mult two matrix together
*/

#include "my_math.h"

double **mult_2_matrix(double **mat1, double **mat2)
{
    int size = 0;
    double **matrix;

    for (; mat1[size] != NULL; size++);
    matrix = malloc(sizeof(double *) * (size+1));
    for (int i = 0; i != size; i++)
        matrix[i] = malloc(sizeof(double) * (size));
    matrix[size] = NULL;
    for (int i = 0; i != size; i++)
        for (int j = 0; j != size; j++) {
            matrix[i][j] = 0;
            for (int k = 0; k != size; k++)
                matrix[i][j] += mat1[i][k] * mat2[k][j];
        }
    return (matrix);
}

double **div_2_matrix(double **mat1, double **mat2)
{
    int size = 0;
    double **matrix;

    for (; mat1[size] != NULL; size++);
    matrix = malloc(sizeof(double *) * (size+1));
    for (int i = 0; i != size; i++)
        matrix[i] = malloc(sizeof(double) * (size));
    matrix[size] = NULL;
    mat2 = inv_matrix(mat2);
    for (int i = 0; i != size; i++)
        for (int j = 0; j != size; j++) {
            matrix[i][j] = 0;
            for (int k = 0; k != size; k++)
                matrix[i][j] += mat1[i][k] * mat2[k][j];
        }
    return (matrix);
}

double **mult_matrix(double **matrix, double nb)
{
    int size = 0;
    for (; matrix[size] != NULL; size++);

    for (int i = 0; i != size; i++)
        for (int j = 0; j != size; j++)
            matrix[i][j] *= nb;
    return (matrix);
}

double **div_matrix(double **matrix, long long nb)
{
    int size = 0;
    for (; matrix[size] != NULL; size++);

    for (int i = 0; i != size; i++)
        for (int j = 0; j != size; j++) {
            //printf("%f %f ")
            matrix[i][j] /= nb;
        }
    return (matrix);
}