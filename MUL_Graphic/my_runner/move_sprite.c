/*
** EPITECH PROJECT, 2018
** move_sprite
** File description:
** move sprites depending of time
*/

#include "csfml.h"
#include <stdlib.h>

void move_obj(sfClock *clock, object_t *obj, float move_x, float move_y)
{
    sfTime time = sfClock_getElapsedTime(clock);
    sfVector2f move = {0, 0};

    move.x = move_x * time.microseconds / 1000000 + obj->pos.x;
    move.y = move_y * time.microseconds / 1000000 + obj->pos.y;
    sfSprite_setPosition(obj->sprite, move);
}

void anim_obj(sfClock *clock, object_t *obj, int start, int end)
{
    sfTime time = sfClock_getElapsedTime(clock);

    obj->rect.left = obj->rect.width * (start-1) + obj->rect.width * \
((int)(time.microseconds * 8 / 1000000) % (end-start+1));
    sfSprite_setTextureRect(obj->sprite, obj->rect);
}

void resize_obj(object_t *obj, float size)
{
    obj->scale.x = size;
    obj->scale.y = size;
    sfSprite_setScale(obj->sprite, obj->scale);
}

void origin_obj(object_t *obj, int pourcent_x, int pourcent_y)
{
    sfVector2f origin;

    origin.x = (obj->rect.width * pourcent_x / 100);
    origin.y = (sfTexture_getSize(obj->texture).y * pourcent_y / 100);
    sfSprite_setOrigin(obj->sprite, origin);
}

void display_loop(sfRenderWindow *window, object_t *obj)
{
    sfVector2f move = sfSprite_getPosition(obj->sprite);
    float x = sfTexture_getSize(obj->texture).x*obj->scale.x - sfRender\
Window_getSize(window).x;
    sfVector2f loop = {(sfTexture_getSize(obj->texture).x*obj->scale.x + \
move.x), 0};

    while (-move.x > sfTexture_getSize(obj->texture).x*obj->scale.x) {
        move.x += sfTexture_getSize(obj->texture).x*obj->scale.x;
        loop.x += sfTexture_getSize(obj->texture).x*obj->scale.x;
    }
    sfRenderWindow_drawSprite(window, obj->sprite, NULL);
    if (-move.x > x) {
        sfSprite_setPosition(obj->sprite, loop);
        sfRenderWindow_drawSprite(window, obj->sprite, NULL);
    }
    sfSprite_setPosition(obj->sprite, move);
}
