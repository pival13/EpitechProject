/*
** EPITECH PROJECT, 2019
** collision.c
** File description:
** collision
*/

#include "my.h"
#include "struct.h"

collision_t *create_collision_struct(obj_t *obj1, obj_t *obj2)
{
    collision_t *coll = malloc(sizeof(collision_t));

    coll->x01 = obj1->pos.x - (obj1->origin.x * obj1->scale.x);
    coll->x02 = obj1->pos.x - (obj1->origin.x * obj1->scale.x) +
    (obj1->rect.width * obj1->scale.x);
    coll->x11 = obj2->pos.x - (obj2->origin.x * obj2->scale.x);
    coll->x12 = obj2->pos.x - (obj2->origin.x * obj2->scale.x) +
    (obj2->rect.width * obj2->scale.x);
    coll->y01 = obj1->pos.y - (obj1->origin.y * obj1->scale.y);
    coll->y02 = obj1->pos.y - (obj1->origin.y * obj1->scale.y) +
    (obj1->rect.height * obj1->scale.x);
    coll->y11 = obj2->pos.y - (obj2->origin.y * obj2->scale.y);
    coll->y12 = obj2->pos.y - (obj2->origin.y * obj2->scale.y) +
    (obj2->rect.height * obj2->scale.y);
    return (coll);
}

int collision_cursor(obj_t *cursor, obj_t *obj)
{
    collision_t *coll = create_collision_struct(cursor, obj);
    float x0 = coll->x01;
    float y0 = coll->y01;

    if (x0 >= coll->x11 && x0 <= coll->x12 &&
        y0 >= coll->y11 && y0 <= coll->y12) {
        free(coll);
        return (1);
    }
    if (x0 >= coll->x11 && x0 <= coll->x12 &&
        y0 >= coll->y11 && y0 <= coll->y12) {
        free(coll);
        return (1);
    }
    free(coll);
    return (0);
}

int collision_entities(obj_t *obj1, obj_t *obj2)
{
    int collision_x = 0;
    int collision_y = 0;
    collision_t *coll = create_collision_struct(obj1, obj2);

    if ((coll->x01 >= coll->x11 && coll->x01 <= coll->x12) ||
        (coll->x02 >= coll->x11 && coll->x02 <= coll->x12))
        collision_x = 1;
    if ((coll->y01 >= coll->y11 && coll->y01 <= coll->y12) ||
        (coll->y02 >= coll->y11 && coll->y02 <= coll->y12))
        collision_y = 1;
    free(coll);
    if (collision_x == 1 && collision_y == 1)
        return (1);
    return (0);
}
