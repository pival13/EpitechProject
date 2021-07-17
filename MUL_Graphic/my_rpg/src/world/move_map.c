/*
** EPITECH PROJECT, 2019
** event
** File description:
** check event
*/

#include "my.h"

static int check_mouse(rpg_t *w, int a)
{
    static sfVector2i pos = {0, 0};
    static int pressed = 0;
    sfVector2i mouse = sfMouse_getPositionRenderWindow(w->win);

    if (!a) {
        pressed = (pressed + 1) % 2;
        pos = sfMouse_getPositionRenderWindow(w->win);
        w->event.type = sfEvtResized;
    }
    if (pressed && ((a == 1 && mouse.y < pos.y - 5) || (a == 2 && mouse.x < \
pos.x - 5) || (a == 3 && mouse.y > pos.y + 5) || (a == 4 && mouse.x > pos.x \
+ 5))) {
        pos = sfMouse_getPositionRenderWindow(w->win);
        return (1);
    }
    return (0);
}

static int check_time(rpg_t *w)
{
    static sfTime time = {0};

    if (time.microseconds < sfClock_getElapsedTime(w->clock).microseconds - \
20000) {
        time = sfClock_getElapsedTime(w->clock);
        return (1);
    }
    return (0);
}

void move_map2(rpg_t *w)
{
    if (KEY(sfKeyR) && check_time(w))
        edit_map(w, NULL, NULL, 0);
    if ((TEXT('z') || TEXT('Z') || check_mouse(w, 1)) && check_time(w))
        edit_map(w, (float[2]){0, -0.02}, (float[2]){0, 0}, 0);
    if ((TEXT('s') || TEXT('S') || check_mouse(w, 3)) && check_time(w))
        edit_map(w, (float[2]){0, 0.02}, (float[2]){0, 0}, 0);
    if ((TEXT('q') || TEXT('Q') || check_mouse(w, 2)) && check_time(w))
        edit_map(w, (float[2]){-0.02, 0}, (float[2]){0, 0}, 0);
    if ((TEXT('d') || TEXT('D') || check_mouse(w, 4)) && check_time(w))
        edit_map(w, (float[2]){0.02, 0}, (float[2]){0, 0}, 0);
    if ((KEY(sfKeyPageDown) || TEXT('+')) && check_time(w))
        edit_map(w, (float[2]){0, 0}, (float[2]){0, 0}, 1);
    if ((KEY(sfKeyPageUp) || TEXT('-')) && check_time(w))
        edit_map(w, (float[2]){0, 0}, (float[2]){0, 0}, -1);
}

void move_map(rpg_t *w)
{
    if (w->event.type == sfEvtMouseButtonPressed || w->event.type == sfEvtMouse\
ButtonReleased)
        check_mouse(w, 0);
    if ((KEY(sfKeyLeft)) && w->event.key.shift == sfTrue && check_time(w))
        edit_map(w, (float[2]){0, 0}, (float[2]){-0.1, 0}, 0);
    if (KEY(sfKeyRight) && w->event.key.shift == sfTrue && check_time(w))
        edit_map(w, (float[2]){0, 0}, (float[2]){0.1, 0}, 0);
    if (KEY(sfKeyUp) && w->event.key.shift == sfTrue && check_time(w))
        edit_map(w, (float[2]){0, 0}, (float[2]){0, -0.1}, 0);
    if (KEY(sfKeyDown) && w->event.key.shift == sfTrue && check_time(w))
        edit_map(w, (float[2]){0, 0}, (float[2]){0, 0.1}, 0);
    move_map2(w);
}
