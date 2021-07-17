/*
** EPITECH PROJECT, 2019
** is_buttonReleased.c
** File description:
** is_buttonreleased
*/

#include "my.h"

sfBool is_button_released(sfMouseButton button, sfRenderWindow *win)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(win, &event)) {
        if (event.mouseButton.button == button &&
            event.type == sfEvtMouseButtonReleased)
            return (sfTrue);
        else
            return (sfFalse);
    }
    return (sfFalse);
}
