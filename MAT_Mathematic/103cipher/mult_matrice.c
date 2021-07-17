/*
** EPITECH PROJECT, 2018
** mult_matrice.c
** File description:
** multipy between matrix
*/

#include "include/my.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int error_management_mult_matrice(int **matrice1, int **matrice2)
{
    int	nb_lin1 = 0;
    int	nb_col1 = 0;
    int	nb_lin2 = 0;
    int	nb_col2 = 0;
    
    for (; matrice1[nb_lin1] != NULL; nb_lin1++);
    for (; matrice1[0][nb_col1] != 0; nb_col1++);
    for	(; matrice2[nb_lin2] != NULL; nb_lin2++);
    for	(; matrice2[0][nb_col2] != 0; nb_col2++);

    if (nb_lin2 != nb_col1)
        return (84);
    return (0);
}

int **mult_matrice(int **matrice1, int **matrice2)
{
    int **matrice_resultat;
    int nb_lin1 = 0;
    int nb_col1 = 0;
    int nb_lin2 = 0;
    int nb_col2 = 0;

    //if (error_management_mult_matrice(matrice1, matrice2) == 84)
    //    exit(84);

    for	(; matrice1[nb_lin1] != NULL; nb_lin1++);
    for (; matrice2[nb_lin2] != NULL; nb_lin2++);
    for (; matrice2[0][nb_col2] != 0; nb_col2++);

    matrice_resultat = malloc(sizeof(int *) * nb_lin1);
    for (int i = 0; i < nb_lin1; i++) {
        matrice_resultat[i] = malloc(sizeof(int) * nb_col2);
        for (int j = 0; j < nb_col2; j++) {
            matrice_resultat[i][j] = 0;
            for (int k = 0; k < nb_lin2; k++)
                matrice_resultat[i][j] += matrice1[i][k] * matrice2[k][j];
        }
    }
    return (matrice_resultat);
}

int error_management_mult_matrice_f(int **matrice1, float **matrice2)
{
    int nb_lin1 = 0;
    int nb_col1 = 0;
    int nb_lin2 = 0;
    int nb_col2 = 0;

    for (; matrice1[nb_lin1] != NULL; nb_lin1++);
    for (; matrice1[0][nb_col1] != 0; nb_col1++);
    for (; matrice2[nb_lin2] != NULL; nb_lin2++);
    for (; matrice2[0][nb_col2] != 0.0; nb_col2++);

    if (nb_lin2 != nb_col1)
	return (84);
    return (0);
}

int **mult_matrice_f(int **matrice1, float **matrice2)
{
    int **matrice_base;
    int nb_lin1 = 0;
    int nb_col1 = 0;
    float nb = 0.0;
    
    //if (error_management_mult_matrice_f(matrice1, matrice2) == 84)
    //exit(84);

    for (; matrice1[nb_lin1] != NULL; nb_lin1++);
    for (; matrice2[nb_col1] != NULL; nb_col1++);
    
    matrice_base = malloc(sizeof(int *) * nb_lin1 + 1);
    for (int i = 0; i < nb_lin1; i++) {
        matrice_base[i] = malloc(sizeof(int) * nb_col1 + 1);
        for (int j = 0; j < nb_col1; j++) {
			nb = 0;
            for (int k = 0; k < nb_col1; k++) {
                nb += matrice1[i][k] * matrice2[k][j];
            }
            matrice_base[i][j] = roundf(nb);
            matrice_base[i][j+1] = 0;
        }
    }
    matrice_base[nb_lin1] = NULL;
    return (matrice_base);
}
