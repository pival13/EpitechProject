/*
** EPITECH PROJECT, 2019
** newton
** File description:
** calcul with newton's method
*/

#include <math.h>
#include <stdio.h>

#define F(x) (coeff[0] + coeff[1]*(x) + coeff[2]*(x)*(x) + coeff[3]*(x)*(x)*(x) + coeff[4]*(x)*(x)*(x)*(x))
#define DF(x) (coeff[1] + 2*coeff[2]*(x) + 3*coeff[3]*(x)*(x) + 4*coeff[4]*(x)*(x)*(x))

void newton(double coeff[5], int accur, double x, int depth)
{
    double y = x - (F(x)/DF(x));
    int acc = accur;

    while ((long long)(x * pow(10, acc)) % 10 == 0)
        if ((long long)(x * pow(10, acc+1)) % 100 == 0)
            acc--;
        else
            break;
    printf("x = %.*f\n", (depth == 1) ? (acc) : (accur), x);
    if (fabs(y-x)/fabs(y) < pow(10, -accur))
        return;
    if (depth > 50) {
        printf("There is no solution\n");
        return;
    }
    newton(coeff, accur, y, depth+1);
}
