/*
** EPITECH PROJECT, 2019
** bissection
** File description:
** solve an equation with the bissection method
*/

#include <math.h>
#include <stdio.h>

#define F(x) (coeff[0] + coeff[1]*(x) + coeff[2]*(x)*(x) + coeff[3]*(x)*(x)*(x) + coeff[4]*(x)*(x)*(x)*(x))

void bissection(double coeff[5], int accur, double x, double y, int depth)
{
    double middle = (x + y) / 2;
    int acc = accur;

    while ((long long)(middle * pow(10, acc)) % 10 == 0)
        if ((long long)(middle * pow(10, acc+1)) % 100 == 0)
            acc--;
        else
            break;
    printf("x = %.*f\n", (acc < depth) ? (accur) : (depth), middle);
    if (middle == y || middle == x)
        return;
    if (F(x) * F(middle) <= 0)
        bissection(coeff, accur, x, middle, depth+1);
    else
        bissection(coeff, accur, middle, y, depth+1);
}
