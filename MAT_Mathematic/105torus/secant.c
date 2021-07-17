/*
** EPITECH PROJECT, 2019
** secant
** File description:
** use the secant's method
*/

#include <math.h>
#include <stdio.h>

#define  F(x) (coeff[0] + coeff[1]*(x) + coeff[2]*(x)*(x) + coeff[3]*(x)*(x)*(x) + coeff[4]*(x)*(x)*(x)*(x))

void secant(double coeff[5], int accur, double x, double y, int depth)
{
    double z = y - (F(y)*(y-x))/(F(y)-F(x));
    int acc = accur;

    while ((long long)(z * pow(10, acc)) % 10 == 0)
        if ((long long)(z * pow(10, acc+1)) % 100 == 0)
            acc--;
        else
            break;
    printf("x = %.*f\n", (depth == 1) ? (acc) : (accur), z);
    if (fabs(z-y)/fabs(z) < pow(10, -accur))
        return;
    if (depth > 50) {
        printf("There is no solution\n");
        return;
    }
    secant(coeff, accur, y, z, depth+1);
}
