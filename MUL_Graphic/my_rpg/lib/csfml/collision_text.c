/*
** EPITECH PROJECT, 2019
** collision_text.c
** File description:
** collision text
*/

#include "my.h"
#include "struct.h"

collision_t *create_collision_struct_t(obj_t *obj1, sfText *obj2)
{
    collision_t *coll = malloc(sizeof(collision_t));
    sfFloatRect rect = sfText_getGlobalBounds(obj2);
    sfVector2f origin = sfText_getOrigin(obj2);
    sfVector2f pos = sfText_getPosition(obj2);

    coll->x01 = obj1->pos.x - (obj1->origin.x * obj1->scale.x);
    coll->x02 = obj1->pos.x - (obj1->origin.x * obj1->scale.x) +
    (obj1->rect.width * obj1->scale.x);
    coll->x11 = pos.x - (origin.x) - 5;
    coll->x12 = pos.x - (origin.x) +
    (rect.width) + 5;
    coll->y01 = obj1->pos.y - (obj1->origin.y * obj1->scale.y);
    coll->y02 = obj1->pos.y - (obj1->origin.y * obj1->scale.y) +
    (obj1->rect.height * obj1->scale.x);
    coll->y11 = pos.y - (origin.y) - 5;
    coll->y12 = pos.y - (origin.y) +
    (rect.height) + 10;
    return (coll);
}

int collision_cursor_text(obj_t *cursor, sfText *obj)
{
    collision_t *coll = create_collision_struct_t(cursor, obj);
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
