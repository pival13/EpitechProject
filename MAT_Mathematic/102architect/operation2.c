/*
** EPITECH PROJECT, 2018
** rotation and reflexion
** File description:
** rotation and reflexion
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415926535897932394626433832

void rotation(float matrice[3][3], char *number)
{
    float angle = atof(number) * PI / 180;
    float copie[3][3] = {{matrice[0][0], matrice[0][1], matrice[0][2]}, {matrice[1][0], matrice[1][1], matrice[1][2]}, {matrice[2][0], matrice[2][1], matrice[2][2]}};
    float rotate[3][3] = {{cos(angle), -sin(angle), 0}, {sin(angle), cos(angle), 0}, {0, 0, 1}};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            matrice[i][j] = 0;
            for (int k  =0; k < 3; k++)
                matrice[i][j] += rotate[i][k] * copie[k][j];
        }
}

void reflection(float matrice[3][3], char *number)
{
    float angle = atof(number) * PI / 180;
    float copie[3][3] = {{matrice[0][0], matrice[0][1], matrice[0][2]}, {matrice[1][0], matrice[1][1], matrice[1][2]}, {matrice[2][0], matrice[2][1], matrice[2][2]}};
    float reflect[3][3] = {{cos(2*angle), sin(2*angle), 0}, {sin(2*angle), -cos(2*angle), 0}, {0, 0, 1}};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            matrice[i][j] = 0;
            for (int k  =0; k < 3; k++)
                matrice[i][j] += reflect[i][k] * copie[k][j];
        }
}
