/*
** EPITECH PROJECT, 2018
** 101pong
** File description:
** pong
*/

#include <stdio.h>
#include <math.h>

int pong(float x0, float y0, float z0, float x1, float y1, float z1, int n)
{
    float x = x1 - x0;
    float y = y1 - y0;
    float z = z1 - z0;
    float const pi = 3.14159265359;

    printf("The velocity vector of the ball is:\n\
(%.2f, %.2f, %.2f)\n\
At time t + %d, ball coordinates will be:\n\
(%.2f, %.2f, %.2f)\n", x, y, z, n, x1+x*n, y1+y*n, z1+z*n);
    if ((z1+z*n) * z1 <= 0)
        printf("The incidence angle is:\n\
%.2f degrees\n", atan(fabs(z)/sqrt(x*x+y*y))*180/pi);
    else
        printf("The ball won't reach the bat.\n");
}
