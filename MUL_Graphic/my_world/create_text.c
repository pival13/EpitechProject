/*
** EPITECH PROJECT, 2019
** create_struct_text
** File description:
** create the struct that contain text
*/

#include "my_world.h"
#include "my.h"
#include <stdlib.h>

void color_text(sfText *text, sfColor color)
{
    sfText_setColor(text, color);
}

void move_text(sfText *text, int x, int y)
{
    sfText_setPosition(text, (sfVector2f){(float)x, (float)y});
}

sfText *create_text(char *str, int size, sfFont *font)
{
    sfText *t = sfText_create();
    sfVector2f origin;

    sfText_setFont(t, font);
    sfText_setString(t, str);
    sfText_setCharacterSize(t, size);
    origin.x = sfText_getGlobalBounds(t).width / 2;
    origin.y = sfText_getGlobalBounds(t).height / 2;
    sfText_setOrigin(t, origin);
    return (t);
}
