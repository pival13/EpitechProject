/*
** EPITECH PROJECT, 2018
** 102architect.c
** File description:
** transform an element
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

int main(int n, char **arg)
{
    float matrice[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    float point[2] = {0, 0};
    float x = 0;
    float y = 0;
    
    if (n < 5) {
        my_printf("Please enter at least 4 params.\n");
        return (84);
    }
    if (my_str_isnum(arg[1]) != 1 || my_str_isnum(arg[2]) != 1) {
        my_printf("Please enter number as second and third params.\n");
        return (84);
    }
    point[0] = atof(arg[1]);
    point[1] = atof(arg[2]);
    arg = &arg[3];
    while (arg[0] != NULL) {


        if (strcmp(arg[0], "-t") == 0) {
            if (arg[1] == NULL || arg[2] == NULL || my_str_isnum(arg[1]) != 1 || my_str_isnum(arg[2]) != 1) {
                my_printf("Please enter two numbers after '-t'.\n");
                return (84);
            }
            printf("Translation along vector (%s, %s)\n", arg[1], arg[2]);
            translation(matrice, arg[1], arg[2]);
            arg = &arg[3];
        }


        else if (strcmp(arg[0], "-z") == 0) {
            if (arg[1] == NULL || arg[2] == NULL || my_str_isnum(arg[1]) != 1 || my_str_isnum(arg[2]) != 1) {
                my_printf("Please enter two numbers after '-z'.\n");
                return (84);
            }
            printf("Scaling by factors %s and %s\n", arg[1], arg[2]);
            scaling(matrice, arg[1], arg[2]);
            arg = &arg[3];
        }


        else if (strcmp(arg[0], "-r") == 0) {
            if (arg[1] == NULL || my_str_isnum(arg[1]) != 1) {
                my_printf("Please enter one number after '-r'.\n");
                return (84);
            }
            printf("Rotation by a %s degree angle\n", arg[1]);
            rotation(matrice, arg[1]);
            arg = &arg[2];
        }


        else if (strcmp(arg[0], "-s") == 0) {
            if (arg[1] == NULL || my_str_isnum(arg[1]) != 1) {
                my_printf("Please enter one number after '-s'.\n");
                return (84);
            }
            printf("Reflection over an axis with an inclination angle of %s degrees\n", arg[1]);
            reflection(matrice, arg[1]);
            arg = &arg[2];
        }


        else {
            my_printf("Please enter either '-t', '-z', '-r' or '-s'.\n");
            return (84);
        }
    }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (matrice[i][j] < 0 && matrice[i][j] > -0.00005)
                matrice[i][j] *= -1;
    printf("%.2f\t%.2f\t%.2f\n%.2f\t%.2f\t%.2f\n%.2f\t%.2f\t%.2f\n", matrice[0][0], matrice[0][1], matrice[0][2], matrice[1][0], matrice[1][1], matrice[1][2], matrice[2][0], matrice[2][1], matrice[2][2]);
    x = matrice[0][0] * point[0] + matrice[0][1] * point[1] + matrice[0][2];
    y = matrice[1][0] * point[0] + matrice[1][1] * point[1] + matrice[1][2];
    
    printf("(%.0f, %.0f) => (%.2f, %.2f)\n", point[0], point[1], x, y);
    return (0);
}
