/*
** EPITECH PROJECT, 2018
** operations.c
** File description:
** operations de 102architect
*/

#include "my.h"
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void translation(float matrice[3][3], char *number1, char *number2)
{
	float nb1 = atof(number1);
    float nb2 = atof(number2);
    float matrice_base[3][3];
    float matrice_operation[3][3] = {{matrice[0][0], matrice[0][1], matrice[0][2]}, {matrice[1][0], matrice[1][1], \
matrice[1][2]}, {matrice[2][0], matrice[2][1], matrice[2][2]}};
    
    matrice_base[0][0] = 1;
    matrice_base[0][1] = 0;
    matrice_base[0][2] = nb1;
    matrice_base[1][0] = 0;
    matrice_base[1][1] = 1;
    matrice_base[1][2] = nb2;
    matrice_base[2][0] = 0;
    matrice_base[2][1] = 0;
    matrice_base[2][2] = 1;
    
    for (int i = 0; i < 3; i++)
    	for (int j = 0; j < 3; j++) {
    		matrice[i][j] = 0;
    		for (int k = 0; k < 3; k++)
    			matrice[i][j] += matrice_base[i][k] * matrice_operation[k][j];
    	}
}

void scaling(float matrice[3][3], char *number1, char *number2)
{
	float nb1 = atof(number1);
    float nb2 = atof(number2);
    float matrice_base[3][3];
    float matrice_operation[3][3] = {{matrice[0][0], matrice[0][1], matrice[0][2]}, {matrice[1][0], matrice[1][1], \
matrice[1][2]}, {matrice[2][0], matrice[2][1], matrice[2][2]}};
    
    matrice_base[0][0] = nb1;
    matrice_base[0][1] = 0;
    matrice_base[0][2] = 0;
    matrice_base[1][0] = 0;
    matrice_base[1][1] = nb2;
    matrice_base[1][2] = 0;
    matrice_base[2][0] = 0;
    matrice_base[2][1] = 0;
    matrice_base[2][2] = 1;

    for (int i = 0; i < 3; i++)
    	for (int j = 0; j < 3; j++) {
    		matrice[i][j] = 0;
    		for (int k = 0; k < 3; k++)
    			matrice[i][j] += matrice_base[i][k] * matrice_operation[k][j];
    	}
}