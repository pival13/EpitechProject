/*
** EPITECH PROJECT, 2019
** event
** File description:
** check event
*/

#include "my.h"
#include "my_world.h"

int passed_text(world_t *w, sfText *text)
{
    sfFloatRect rect = {sfText_getGlobalBounds(text).left*SIZE(x\
)/BSIZE(width), sfText_getGlobalBounds(text).top*SIZE(y)/BSIZE(h\
eight), sfText_getGlobalBounds(text).width*SIZE(x)/BSIZE(width), \
sfText_getGlobalBounds(text).height*SIZE(y)/BSIZE(height)};
    sfVector2i mouse = sfMouse_getPositionRenderWindow(w->window);

    if (mouse.x <= rect.width + rect.left && mouse.x >= rect.lef\
t && mouse.y <= rect.height + rect.top && mouse.y >= rect.top) {
        color_text(text, sfWhite);
        if (w->event.type == sfEvtMouseButtonPressed)
            return (1);
    } else
        color_text(text, sfBlack);
    return (0);
}

int passed_button(world_t *w, sfRectangleShape *button)
{
    sfFloatRect rect = {sfRectangleShape_getGlobalBounds(button).lef\
t*SIZE(x)/BSIZE(width), sfRectangleShape_getGlobalBounds(button).top\
*SIZE(y)/BSIZE(height), sfRectangleShape_getGlobalBounds(button).wid\
th*SIZE(x)/BSIZE(width), sfRectangleShape_getGlobalBounds(button).he\
ight*SIZE(y)/BSIZE(height)};
    sfVector2i mouse = sfMouse_getPositionRenderWindow(w->window);

    if (mouse.x <= rect.width + rect.left && mouse.x >= rect.left && mouse.y \
<= rect.height + rect.top && mouse.y >= rect.top && cmp_color(sfRectangleShap\
e_getOutlineColor(button), sfRed) != 1) {
        sfRectangleShape_setOutlineColor(button, sfWhite);
        if (w->event.type == sfEvtMouseButtonPressed) {
            for (int i = 0; i != 13; i++)
                sfRectangleShape_setOutlineColor(w->page[1].rbutton[i], sfTran\
sparent);
            return (1);
        }
    } else if (cmp_color(sfRectangleShape_getOutlineColor(button), sfRed) != 1)
        sfRectangleShape_setOutlineColor(button, sfTransparent);
    return (0);
}

int passed_shape(sfVector2f mouse, sfConvexShape *shape, world_t *w)
{
    sfVector2f p[4] = {sfConvexShape_getPoint(shape, 0), sfConvexShape_getPoint\
(shape, 1), sfConvexShape_getPoint(shape, 2), sfConvexShape_getPoint(shape, 3)};

    if (mouse.y >= (p[0].y-p[1].y)/(p[0].x-p[1].x)*(mouse.x-p[1].x)+p[1].y && m\
ouse.y <= (p[2].y-p[3].y)/(p[2].x-p[3].x)*(mouse.x-p[3].x)+p[3].y && mouse.y <\
= (p[2].y-p[1].y)/(p[2].x-p[1].x)*(mouse.x-p[1].x)+p[1].y && mouse.y >= (p[0].\
y-p[3].y)/(p[0].x-p[3].x)*(mouse.x-p[3].x)+p[3].y) {
        if (w->event.type == sfEvtMouseButtonPressed)
            return (1);
        else {
            sfConvexShape_setOutlineColor(shape, sfRed);
            sfConvexShape_setOutlineThickness(shape, 2);
        }
    }
    return (0);
}
