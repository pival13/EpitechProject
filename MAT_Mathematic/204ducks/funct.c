/*
** EPITECH PROJECT, 2020
** 204ducks_2019 [WSL: Ubuntu]
** File description:
** check
*/

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

double a;
double esp;

double integral(double min, double max, double (*f)(double))
{
    int n = max*200;
    double delta = (max-min) / n;
    double result = 0;

    for (int i = 0; i <= n; i++)
        if (i == 0 || i == n)
            result += f(min + i*delta);
        else if (i % 2 == 1)
            result += 4*f(min + i*delta);
        else
            result += 2*f(min + i*delta);
    return result * delta / 3;
}

double funct_204(double t)
{
    return a*exp(-t) + (4-3*a)*exp(-2*t) + (2*a-4)*exp(-4*t);
}

double e_204(double t)
{
    return t*(a*exp(-t) + (4-3*a)*exp(-2*t) + (2*a-4)*exp(-4*t));
}

double v_204(double t)
{
    return pow(t-esp, 2)*(a*exp(-t) + (4-3*a)*exp(-2*t) + (2*a-4)*exp(-4*t));
}

double percent_204(double percent)
{
    double i = 1;
    for (; integral(0, i/60, funct_204) * 100 < percent; i += 0.01)
        ;//printf("%lf: %lf\n", i, integral(0, i/60, funct_204));
    return i;
}

int main(int n, char **arg)
{
    if (n == 4 && !strcmp(arg[1], "proba")) {
        a = atof(arg[2]);
        printf("%.3f\n", funct_204(atof(arg[3])));
    } else if (n == 5 && !strcmp(arg[1], "integral")) {
        a = atof(arg[2]);
        printf("%lf\n", integral(atof(arg[3]), atof(arg[4]), funct_204));
    } else if (n == 3 && !strcmp(arg[1], "esperance")) {
        a = atof(arg[2]);
        printf("%lf\n", integral(0, 200, e_204));
    } else if (n == 3 && !strcmp(arg[1], "deviation")) {
        a = atof(arg[2]);
        esp = integral(0, 50, e_204);
        printf("%.3f\n", sqrt(integral(0, 50, v_204)));
    } else if (n == 4 && !strcmp(arg[1], "percent")) {
        a = atof(arg[2]);
        printf("%lf\n", percent_204(atof(arg[3])));
    } else
        return 84;
}