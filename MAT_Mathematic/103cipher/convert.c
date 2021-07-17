/*
** EPITECH PROJECT, 2018
** convert
** File description:
** convert the key and the string
*/

#include "my.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define NB_ROW (nb_row%size != 0) ? (nb_row/size+1) : (nb_row/size)

int **create_key(char *ckey)
{
    int **key;
    int size = 0;

    for (size = 0; strlen(ckey) > size*size; size++);
    key = malloc(sizeof(int *) * (size+1));
    for (int i = 0; i != size; i++) {
        key[i] = malloc(sizeof(int) * (size+1));
        for (int j = 0; j != size; j++) {
            if (i*size+j < strlen(ckey))
                key[i][j] = ckey[i*size+j];
            else
                key[i][j] = 0;
            key[i][j+1] = 0;
        }
        key[i+1] = NULL;
    }
    return (key);
}

int **create_str(char *cstr, int **key)
{
    int **str;
    int size = 0;
    int nb_row = strlen(cstr);

    for (size = 0; key[size] != NULL; size++);
    nb_row = NB_ROW;
    str = malloc(sizeof(int *) * (nb_row + 1));
    for (int i = 0; i < nb_row; i++) {
        str[i] = malloc(sizeof(int) * (size+1));
        for (int j = 0; j != size; j++) {
            if (i*size+j < strlen(cstr))
                str[i][j] = cstr[i*size+j];
            else
                str[i][j] = 0;
            str[i][j+1] = 0;
        }
        str[i+1] = NULL;
    }
    return (str);
}

int count_number(char *cstr)
{
    int nb = 1;

    for (int i = 0; cstr[i+1] != '\0'; i++)
        if (cstr[i] == ' ' && cstr[i+1] >= '0' && cstr[i+1] <= '9')
            nb++;
    return (nb);
}

int **create_matrix(char *cstr, int **key)
{
    int **str;
    int size = 0;
    int nb_row = count_number(cstr);

    if (my_str_isnum(cstr) == 0)
        exit(84);
    for (size = 0; key[size] != NULL; size++);
    nb_row = NB_ROW;
    str = malloc(sizeof(int *) * (nb_row + 1));
    for (int i = 0; i < nb_row; i++) {
        str[i] = malloc(sizeof(int) * (size + 1));
        for (int j = 0; j != size; j++) {
            if (my_strlen(cstr) > 2) {
                str[i][j] = my_getnbr(cstr);
                for (;cstr[0] >= '0' && cstr[0] <= '9'; cstr++);
                for (;cstr[0] == ' '; cstr++);
            } else
                str[i][j] = 0;
            str[i][j+1] = 0;
        }
        str[i+1] = NULL;
    }
    return (str);
}
