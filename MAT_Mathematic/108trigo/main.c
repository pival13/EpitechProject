/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of 108trigo
*/

#include "my_math.h"
#include <stdio.h>
#include <string.h>

int main(int n, char **arg)
{
    double **matrix;

    if (n < 3 || sqrt(n-2) - (int)sqrt(n-2) != (double)0)
        return (84);
    for (int i = 2; i != n; i++)
        if (is_float(arg[i]) == 0)
            return (84);
    matrix = create_matrix(&arg[2], sqrt(n-2));
    if (strcmp(arg[1], "COS") == 0)
        matrix = cos_matrix(matrix);
    else if (strcmp(arg[1], "SIN") == 0)
        matrix = sin_matrix(matrix);
    else if (strcmp(arg[1], "EXP") == 0)
        matrix = exp_matrix(matrix);
    else if (strcmp(arg[1], "COSH") == 0)
        matrix = cosh_matrix(matrix);
    else if (strcmp(arg[1], "SINH") == 0)
        matrix = sinh_matrix(matrix);
    else
        return (84);
    for (int i = 0; i != sqrt(n-2); i++) {
        for (int j = 0; j != sqrt(n-2); j++) {
            printf("%.2lf", matrix[i][j]);
            if (j+1 != sqrt(n-2))
                printf("\t");
        }
        printf("\n");
    }
    return (0);
}
