/*
** EPITECH PROJECT, 2019
** div_fact_matrix
** File description:
** divide a matrix by a factoriel
*/

#include "my_math.h"

double **div_fact_mat(double **matrix, int nb)
{
    int size = 0;
    for (; matrix[size] != NULL; size++);

    for (int k = 1; k <= nb; k++) {
        for (int i = 0; i != size; i++)
            for (int j = 0; j != size; j++) {
                matrix[i][j] /= k;
            }
    }
    return (matrix);
}