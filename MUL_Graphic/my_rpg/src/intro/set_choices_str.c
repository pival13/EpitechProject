/*
** EPITECH PROJECT, 2019
** set_choices_str.c
** File description:
** set choices str
*/

#include "my.h"

void set_choices_str(char *manip, char *manip1, char *manip2, char *str)
{
    int z = 0;

    for (int i = 0; str[z] != ';' && str[z] != 0; i++, z++) {
        manip[i] = str[z];
        (i % 28 == 0 && i != 0) ? (i++, manip[i] = '\n') : (0);
    }
    (str[z] == ';') ? (z++) : (0);
    for (int i = 0; str[z] != ';' && str[z] != 0; i++, z++) {
        manip1[i] = str[z];
        (i % 28 == 0 && i != 0) ? (i++, manip1[i] = '\n') : (0);
    }
    (str[z] == ';') ? (z++) : (0);
    for (int i = 0; str[z] != 0; i++, z++) {
        manip2[i] = str[z];
        (i % 28 == 0 && i != 0) ? (i++, manip2[i] = '\n') : (0);
    }
}
