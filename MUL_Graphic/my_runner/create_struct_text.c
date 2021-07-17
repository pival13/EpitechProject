/*
** EPITECH PROJECT, 2019
** create_struct_text
** File description:
** create the struct that contain text
*/

#include "csfml.h"
#include "my.h"
#include <stdlib.h>

text_t *create_text(char *str, int x, int y)
{
    text_t *t = malloc(sizeof(text_t));

    t->text = sfText_create();
    t->font = sfFont_createFromFile("sprite/arial.ttf");
    sfText_setFont(t->text, t->font);
    sfText_setString(t->text, str);
    t->origin.x = sfText_getGlobalBounds(t->text).width / 2;
    t->origin.y = sfText_getGlobalBounds(t->text).height / 2;
    sfText_setOrigin(t->text, t->origin);
    t->pos.x = x;
    t->pos.y = y;
    sfText_setPosition(t->text, t->pos);
    return (t);
}
