/*
** EPITECH PROJECT, 2019
** set_anim_sprite.c
** File description:
** set anim sprite
*/

#include "my.h"

int set_anim_sprite_ver(obj_t *obj, int ite)
{
    sfIntRect rect = sfSprite_getTextureRect(obj->sprite);
    sfVector2u texture_size = sfTexture_getSize(obj->texture);

    rect.top = rect.height * ite;
    if (rect.top >= (float)texture_size.y + rect.height)
        rect.top = 0;
    obj->rect = rect;
    sfSprite_setTextureRect(obj->sprite, rect);
    return (0);
}

int set_anim_sprite_hor(obj_t *obj, int ite)
{
    sfIntRect rect = sfSprite_getTextureRect(obj->sprite);
    sfVector2u texture_size = sfTexture_getSize(obj->texture);

    rect.left = rect.width * ite;
    if (rect.left >= (float)texture_size.x + rect.width)
        rect.left = 0;
    obj->rect = rect;
    sfSprite_setTextureRect(obj->sprite, rect);
    return (0);
}

int set_anim_sprite(obj_t *obj, int sens, int ite)
{
    if (sens == 0)
        set_anim_sprite_hor(obj, ite);
    else if (sens == 1)
        set_anim_sprite_ver(obj, ite);
    else
        return (84);
    return (0);
}
