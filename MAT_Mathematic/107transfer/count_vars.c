/*
** EPITECH PROJECT, 2019
** count_vars.c
** File description:
** count vars functions
*/

#include "my.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int count_numbers(char *str)
{
    int nb = 1;

    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == '*')
            nb++;
    }
    return(nb);
}

char *clean_word(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        str[i] = 0;
    return (str);
}

double *numbers_per_line(char *str)
{
    char *nb = malloc(sizeof(char) * (my_strlen(str) + 1));
    double *vars = malloc(sizeof(double) * (count_numbers(str) + 1));
    int k = 0;

    for (int i = 0; i < my_strlen(str); i++, nb[i] = 0);
    for (int i = 0; i < count_numbers(str); i++, vars[i] = -84.84);
    for (int i = 0, j = 0; str[i] != 0; i++) {
        if (str[i] != '*') {
            nb[j] = str[i];
            j++;
        } else {
            j = 0;
            vars[k] = atof(nb);
            k++;
            nb = clean_word(nb);
        }
        /*if (str[i+1] == 0) {
            j = 0;
            vars[k] = atof(nb);
            k++;
            nb = clean_word(nb);
            }*/
    }
    vars[k] = atof(nb);
    return (vars);
}

void print_double_tab(double **vars)
{
    for (int i = 0; vars[i] != NULL; i++) {
        for (int j = 0; vars[i][j] != -84.84; j++) {
            printf("%f ",vars[i][j]);
        }
        printf("\n");
    }
}

int *measure_vars(double **vars)
{
    int *size;
    int nb_col = 0;

    for (; vars[nb_col] != NULL; nb_col++);
    size = malloc(sizeof(int) * (nb_col + 1));
    for (int i = 0; i < nb_col; i++)
        size[i] = 0;
    for (int i = 0; vars[i] != NULL; i++) {
        for (int j = 0; vars[i][j] != -84.84; j++) {
            size[i] += 1;
        }
    }
    size[nb_col] = 0;
    return (size);
}
