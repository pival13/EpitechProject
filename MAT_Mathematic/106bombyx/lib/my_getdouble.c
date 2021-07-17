/*
** EPITECH PROJECT, 2018
** my_get_float.c
** File description:
** str to float
*/

#include "../include/my.h"

double my_getdouble2(char *toconvert, int point_pos, double number, int mult)
{
    double mult2 = 0.1;

    for (int i = point_pos - 1; i >= 0; i--) {
        number += (toconvert[i] - 48) * mult;
        mult *= 10;
    }
    for (int i = point_pos + 1; toconvert[i] != 0; i++) {
        number += (toconvert[i] - 48) * mult2;
        mult2 /= 10;
    }
    return (number);
}

double negative_double(double number, int negative)
{
    if (negative == 1)
        number *= (-1);
    return (number);
}

double my_getdouble(char *toconvert)
{
    double number = 0.000;
    int point_pos = 0;
    int mult = 1;
    int negative = 0;
    int i = 0;

    if (toconvert[0] == '-') {
        negative = 1;
        toconvert++;
    }
    for (; toconvert[i] != 0; i++)
        if (toconvert[i] == '.')
            point_pos = i;
    if (point_pos == 0) {
        for (i--; i >= 0; i--, mult *= 10)
            number += (toconvert[i] - 48) * mult;
    } else
        number = my_getdouble2(toconvert, point_pos, number, mult);
    number = negative_double(number, negative);
    return (number);
}
