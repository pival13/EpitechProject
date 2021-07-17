/*
** EPITECH PROJECT, 2019
** edit_map
** File description:
** edit the map
*/

#include "my_world.h"
#include <math.h>

int find_ijcoeff(world_t *w, int type, float angle[2])
{
    int i = 0;
    int j = 0;
    int coeff = 0;

    for (; w->map[i] != NULL; i++);
    for (; w->map[0][j].height != -100; j++);
    if (-SIZE(x)/(cos(angle[0])*(j-1)+sin(angle[0])*(i-1)) > 3*SIZE(y)/4/(-sin\
(angle[0])*sin(angle[1])*j-cos(angle[0])*sin(angle[1])*i))
        coeff = 3*SIZE(y)/4/(-sin(angle[0])*sin(angle[1])*j-cos(angle[0])*sin(\
angle[1])*i);
    else
        coeff = -SIZE(x)/(cos(angle[0])*(j-1)+sin(angle[0])*(i-1));
    if (type == 1)
        return (i);
    else if (type == 2)
        return (j);
    else
        return (coeff);
}

void calculate_map(world_t *w, int coeff, float angle[2], float init_pos[2])
{
    for (int y = 0; w->map[y] != NULL; y++)
        for (int x = 0; w->map[y][x].height != -100; x++) {
            w->map[y][x].pos.x = (cos(angle[0])*y-sin(angle[0])*x - init_pos[\
0]) * coeff / SIZE(x)*BSIZE(width) + BSIZE(width)/2;
            w->map[y][x].pos.y = (-sin(angle[0])*sin(angle[1])*y-cos(angle[0]\
)*sin(angle[1])*x - cos(angle[1])/2*w->map[y][x].height - init_pos[1]) * coef\
f / SIZE(y)*BSIZE(height) + BSIZE(height);
            if (x > 0 && y > 0) {
                sfConvexShape_setPoint(w->map[y-1][x-1].shape, 0, w->map[y-1]\
[x-1].pos);
                sfConvexShape_setPoint(w->map[y-1][x-1].shape, 1, w->map[y]\
[x-1].pos);
                sfConvexShape_setPoint(w->map[y-1][x-1].shape, 2, w->map[y]\
[x].pos);
                sfConvexShape_setPoint(w->map[y-1][x-1].shape, 3, w->map[y-1]\
[x].pos);
            }
        }
}

void edit_map(world_t *w, float change_angle[2], float change_pos[2], flo\
at change_size)
{
    static int coeff = 0;
    static float angle[2] = {-2.3561945, 0.5235988};
    static float init_pos[2] = {0, 0};
    int max[2] = {find_ijcoeff(w, 1, angle), find_ijcoeff(w, 2, angle)};
    if ((init_pos[0] == 0 && init_pos[1] == 0) || change_angle == NULL) {
        angle[0] = -2.3561945;
        angle[1] = 0.5235988;
        init_pos[0] = sqrt(2)/2*((float)(max[0]+max[1])/2-max[0]);
        init_pos[1] = -sin(angle[0])*sin(angle[1])*(max[0]-1) - cos(angle[\
0])*sin(angle[1])*(max[1]-1);
    } else {
        init_pos[0] += change_pos[0];
        init_pos[1] += change_pos[1];
        angle[0] += change_angle[0];
        angle[1] += change_angle[1];
    }
    if (coeff == 0 || w->event.type == sfEvtResized || change_angle == NULL)
        coeff = find_ijcoeff(w, 0, angle);
    coeff += change_size;
    calculate_map(w, coeff, angle, init_pos);
}
