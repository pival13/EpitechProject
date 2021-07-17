/*
** EPITECH PROJECT, 2019
** event
** File description:
** check event
*/

#include "my.h"
#include "my_world.h"

void edit_map_height(world_t *w, int a, int b, int height)
{
    w->map[a][b].height += height;
    edit_map(w, (float[2]){0, 0}, (float[2]){0, 0}, 0);
}

void change_map2(world_t *w, int type, sfVector2f mouse, int i)
{
    for (int j = 0; w->map[i][j].height != -100; j++) {
        if (mouse.x > w->map[i][j].pos.x-20 && mouse.x < w->map[i][j].pos.\
x+20 && mouse.y > w->map[i][j].pos.y-20 && mouse.y < w->map[i][j].pos.y+20 && \
(type == 1 || type == -1)) {
            if (w->event.type != sfEvtMouseButtonPressed) {
                sfCircleShape_setPosition(w->circle, w->map[i][j].pos);
                sfRenderWindow_drawCircleShape(w->window, w->circle, NULL);
            } else
                edit_map_height(w, i, j, type);
        }
        if (type < -6 && i > 0 && j > 0 && passed_shape(mouse, w->map[i-1]\
[j-1].shape, w) == 1)
            sfConvexShape_setTexture(w->map[i-1][j-1].shape, w->texture[(ty\
pe-1)/-2-7], sfTrue);
    }
}

void change_map(world_t *w, int type)
{
    sfVector2f mouse = {(float)sfMouse_getPositionRenderWindow(w->window).x/SIZ\
E(x)*BSIZE(width), (float)sfMouse_getPositionRenderWindow(w->window).y/SIZE(y)*\
BSIZE(height)};

    for (int i = 1; w->map[i] != NULL; i++)
        for (int j = 1; w->map[i][j].height != -100; j++) {
            sfConvexShape_setOutlineColor(w->map[i-1][j-1].shape, sfBlack);
            sfConvexShape_setOutlineThickness(w->map[i-1][j-1].shape, 1);
        }
    for (int i = 0; w->map[i] != NULL; i++)
        change_map2(w, type, mouse, i);
    while (w->event.type == sfEvtMouseButtonPressed)
        sfRenderWindow_pollEvent(w->window, &w->event);
}

void move_map2(world_t *w, int *type)
{
    if (TEXT('r') || *type == -5)
        edit_map(w, NULL, NULL, 0);
    if (TEXT('z') || *type == -3)
        edit_map(w, (float[2]){0, -0.02}, (float[2]){0, 0}, 0);
    if (TEXT('s') || *type == -7)
        edit_map(w, (float[2]){0, 0.02}, (float[2]){0, 0}, 0);
    if (TEXT('q') || *type == -9)
        edit_map(w, (float[2]){-0.02, 0}, (float[2]){0, 0}, 0);
    if (TEXT('d') || *type == -11)
        edit_map(w, (float[2]){0.02, 0}, (float[2]){0, 0}, 0);
    while (w->event.type == sfEvtMouseWheelScrolled)
        sfRenderWindow_pollEvent(w->window, &w->event);
    if (*type <= -3 && *type >= -11) {
        for (int i = 2; i != 7; i++)
            sfRectangleShape_setOutlineColor(w->page[1].rbutt\
on[i], sfTransparent);
        *type = 0;
    }
}

void move_map(world_t *w, int *type)
{
    change_map(w, *type);
    if (KEY(sfKeyLeft))
        edit_map(w, (float[2]){0, 0}, (float[2]){0.05, 0}, 0);
    if (KEY(sfKeyRight))
        edit_map(w, (float[2]){0, 0}, (float[2]){-0.05, 0}, 0);
    if (KEY(sfKeyUp))
        edit_map(w, (float[2]){0, 0}, (float[2]){0, 0.05}, 0);
    if (KEY(sfKeyDown))
        edit_map(w, (float[2]){0, 0}, (float[2]){0, -0.05}, 0);
    if (KEY(sfKeyPageDown) || TEXT('+') || SCROLL(>))
        edit_map(w, (float[2]){0, 0}, (float[2]){0, 0}, 1);
    if (KEY(sfKeyPageUp) || TEXT('-') || SCROLL(<))
        edit_map(w, (float[2]){0, 0}, (float[2]){0, 0}, -1);
    move_map2(w, type);
}
