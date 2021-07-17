/*
** EPITECH PROJECT, 2019
** is_in_radius.c
** File description:
** an obj is near to another obj or not
*/

#include "my.h"

float my_sqrt(float x)
{
    float result = 0;
    float resultx = 0;

    for (result = 0.01; resultx < x; result += 0.01) {
        resultx = result * result;
    }
    return (result);
}

radius_coll *create_rcoll(obj_t *obj1, obj_t *obj2, float rad)
{
    radius_coll *rad_coll = malloc(sizeof(radius_coll));

    rad_coll->radius = rad;
    rad_coll->rx = obj1->pos.x - obj1->origin.x + (obj1->rect.width / 2);
    rad_coll->ry = obj1->pos.y - obj1->origin.y + (obj1->rect.height / 2);
    rad_coll->x1 = obj2->pos.x - obj2->origin.x;
    rad_coll->y1 = obj2->pos.y - obj2->origin.y;
    rad_coll->x2 = obj2->pos.x - obj2->origin.x + obj2->rect.width;
    rad_coll->y2 = obj2->pos.y - obj2->origin.y + obj2->rect.height;
    return (rad_coll);
}

int is_in_radius(obj_t *obj1, obj_t *obj2, float radius)
{
    radius_coll *rad_coll = create_rcoll(obj1, obj2, radius);
    int res = 0;
    int testx = rad_coll->x2;
    int testy = rad_coll->y2;
    float distx = 0;
    float disty = 0;
    float distance = 0;

    if (rad_coll->rx < rad_coll->x1)
        testx = rad_coll->x1;
    if (rad_coll->ry < rad_coll->y1)
        testy = rad_coll->y1;
    distx = rad_coll->rx - testx;
    disty = rad_coll->ry - testy;
    distance = distx * distx + disty * disty;
    distance = my_sqrt(distance);
    (distance <= radius) ? (res = 1) : (0);
    free(rad_coll);
    return (res);
}
