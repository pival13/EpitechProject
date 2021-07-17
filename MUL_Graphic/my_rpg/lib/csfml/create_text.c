/*
** EPITECH PROJECT, 2019
** create_text.c
** File description:
** create sftext
*/

#include "my.h"

sfText *create_text(char *str, int size, sfFont *font)
{
    sfText *t = sfText_create();

    sfText_setFont(t, font);
    sfText_setString(t, str);
    sfText_setCharacterSize(t, size);
    sfText_setColor(t, sfBlack);
    return (t);
}

void edit_text(sfText *t, char *str, float x, float y)
{
    if (str != NULL)
        sfText_setString(t, str);
    sfText_setColor(t, sfBlack);
    sfText_setPosition(t, (sfVector2f){x, y});
}

void edit_text_str(sfText *t, char *str)
{
    if (str != NULL)
        sfText_setString(t, str);
}

void edit_text_color(sfText *t, float r, float g, float b)
{
    sfColor color = {r, g, b, 255};

    sfText_setColor(t, color);
}
