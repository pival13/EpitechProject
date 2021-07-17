/*
** EPITECH PROJECT, 2019
** anim_sprite.c
** File description:
** anim sprite
*/

#include "my.h"

int anim_sprite_ver(obj_t *obj, int ite)
{
    sfIntRect rect = sfSprite_getTextureRect(obj->sprite);
    sfVector2u texture_size = sfTexture_getSize(obj->texture);

    for (int i = 0; i < ite; i++)
        rect.top += rect.height;
    if (rect.top >= (float)texture_size.y)
        rect.top = 0;
    obj->rect = rect;
    sfSprite_setTextureRect(obj->sprite, rect);
    return (0);
}

int anim_sprite_hor(obj_t *obj, int ite)
{
    sfIntRect rect = sfSprite_getTextureRect(obj->sprite);
    sfVector2u texture_size = sfTexture_getSize(obj->texture);

    for (int i = 0; i < ite; i++)
        rect.left += rect.width;
    if (rect.left >= (float)texture_size.x)
        rect.left = 0;
    obj->rect = rect;
    sfSprite_setTextureRect(obj->sprite, rect);
    return (0);
}

int anim_sprite(obj_t *obj, int sens, int ite)
{
    if (sens == 0)
        anim_sprite_hor(obj, ite);
    else if (sens == 1)
        anim_sprite_ver(obj, ite);
    else
        return (84);
    return (0);
}
