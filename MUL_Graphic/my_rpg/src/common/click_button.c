/*
** EPITECH PROJECT, 2019
** click_button.c
** File description:
** click_button
*/

#include "my.h"

int click_button(obj_t *cursor, obj_t *button, sfEvent event)
{
    if (collision_cursor(cursor, button) == 1
        && event.type == sfEvtMouseButtonReleased &&
        event.mouseButton.button == sfMouseLeft) {
        return (1);
    }
    return (0);
}

int click_button_text(obj_t *cursor, sfText *button, sfEvent event)
{
    if (collision_cursor_text(cursor, button) == 1
        && event.type == sfEvtMouseButtonReleased &&
        event.mouseButton.button == sfMouseLeft) {
        return (1);
    }
    return (0);
}
