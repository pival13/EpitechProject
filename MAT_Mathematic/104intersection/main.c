/*
** EPITECH PROJECT, 2018
** 104intersection
** File description:
** check if a ray of light cross an object
*/

#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int sphere(float light[6], float radius, char **arg)
{
    float a = light[3]*light[3] + light[4]*light[4] + light[5]*light[5];
    float b = (2*(light[0]*light[3] + light[1]*light[4] + light[2]*light[5]));
    float c = light[0]*light[0] + light[1]*light[1] + light[2]*light[2] - radius * radius;
    float nb[2] = {0, 0};
    float delta = b * b - 4 * a * c;

    printf("Sphere of radius %s\nLine passing through the point (%s, %s, %s) and parallel to the vector (%s, %s, %s)\n", arg[8], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7]);
    if (delta < 0)
        write(1, "No intersection point.\n", 23);
    if (delta == 0) {
        nb[0] = - (b / (2 * a));
        printf("1 intersection point:\n(%.3f, %.3f, %.3f)\n", light[0] + nb[0] * light[3], light[1] + nb[0] * light[4], light[2] + nb[0] * light[5]);
    }
    if (delta > 0) {
        nb[0] = -(b - sqrt(delta)) / (2 * a);
        nb[1] = -(b + sqrt(delta)) / (2 * a);
        printf("2 intersection points:\n");
        printf("(%.3f, %.3f, %.3f)\n", light[0] + nb[0] * light[3], light[1] + nb[0] * light[4], light[2] + nb[0] * light[5]);
        printf("(%.3f, %.3f, %.3f)\n", light[0] + nb[1] * light[3], light[1] + nb[1] * light[4], light[2] + nb[1] * light[5]);
    }
    return (0);
}

int cylinder(float light[6], float radius, char **arg)
{
    float a = light[3]*light[3] + light[4]*light[4];
    float b = 2*(light[0]*light[3] + light[1]*light[4]);
    float c = light[0]*light[0] + light[1]*light[1] - radius * radius;
    float nb[2] = {0, 0};
    float delta = b * b - 4 * a * c;

    printf("Cylinder of radius %s\nLine passing through the point (%s, %s, %s) and parallel to the vector (%s, %s, %s)\n", arg[8], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7]);
    if (light[3] == 0 && light[4] == 0) {
        if (light[0] * light[0] + light[1] * light[1] == radius * radius)
            return (printf("There is an infinite number of intersection points.\n"));
        else
            return (printf("No intersection point.\n"));
    }
    if (delta < 0)
        printf("No intersection point.\n");
    if (delta == 0) {
        nb[0] = - (b / (2 * a));
        printf("1 intersection point:\n(%.3f, %.3f, %.3f)\n", light[0] + nb[0] * light[3], light[1] + nb[0] * light[4], light[2] + nb[0] * light[5]);
    }
    if (delta > 0) {
        nb[0] = -(b - sqrt(delta)) / (2 * a);
        nb[1] = -(b + sqrt(delta)) / (2 * a);
        printf("2 intersection points:\n");
        printf("(%.3f, %.3f, %.3f)\n", light[0] + nb[0] * light[3], light[1] + nb[0] * light[4], light[2] + nb[0] * light[5]);
        printf("(%.3f, %.3f, %.3f)\n", light[0] + nb[1] * light[3], light[1] + nb[1] * light[4], light[2] + nb[1] * light[5]);
    }
    return (0);
}

int cone(float light[6], float angle, char **arg)
{
    float a = light[3]*light[3] + light[4]*light[4] - (light[5]*light[5]*tan(angle)*tan(angle));
    float b = 2*(light[0]*light[3] + light[1]*light[4] - (light[2]*light[5]*tan(angle)*tan(angle)));
    float c = light[0]*light[0] + light[1]*light[1] - (light[2]*light[2]*tan(angle)*tan(angle));
    float nb[2] = {0, 0};
    float delta = b * b - 4 * a * c;
    float contact = light[0]*light[0] + light[1]*light[1] - light[2]*light[2]*tan(angle)*tan(angle);

    printf("Cone with a %s degree angle\nLine passing through the point (%s, %s, %s) and parallel to the vector (%s, %s, %s)\n", arg[8], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7]);
    if (delta < -0.0001)
        printf("No intersection point.\n");
    else if (delta > 0.0001) {
        nb[0] = -(b - sqrt(delta)) / (2 * a);
        nb[1] = -(b + sqrt(delta)) / (2 * a);
        printf("2 intersection points:\n");
        printf("(%.3f, %.3f, %.3f)\n", light[0] + nb[0] * light[3], light[1] + nb[0] * light[4], light[2] + nb[0] * light[5]);
        printf("(%.3f, %.3f, %.3f)\n", light[0] + nb[1] * light[3], light[1] + nb[1] * light[4], light[2] + nb[1] * light[5]);
    } else {
        if (contact > -0.0001 && contact < 0.0001)
            return (printf("There is an infinite number of intersection points.\n"));
        nb[0] = - (b / (2 * a));
        printf("1 intersection point:\n(%.3f, %.3f, %.3f)\n", light[0] + nb[0] * light[3], light[1] + nb[0] * light[4], light[2] + nb[0] * light[5]);
    }
    return (0);
}

int main(int n, char **arg)
{
    int ver = 0;
    float light[6] = {0, 0, 0, 0, 0, 0};
    float radius = 0;

    if (n != 9)
        return (84);
    for (int i = 1; i != 9; i++)
        if (my_str_isint(arg[1]) == 0 || my_str_isfloat(arg[i]) == 0)
            return (84);
    ver = atoi(arg[1]);
    if (ver < 1 || ver > 3)
        return (84);
    for (int i = 0; i != 6; i++)
        light[i] = atof(arg[i+2]);
    radius = atof(arg[8]);
    if (ver == 3) {
        if (radius > 90 || radius < -90 || (light[3] == 0 && light[4] == 0 && light[5] == 0))
            return (84);
        cone(light, fabs(radius * M_PI / 180), arg);
    }
    if ((light[3] == 0 && light[4] == 0 && light[5] == 0) || radius <= 0)
        return (84);
    if (ver == 1)
        sphere(light, radius, arg);
    if (ver == 2)
        cylinder(light, radius, arg);
    return (0);
}
