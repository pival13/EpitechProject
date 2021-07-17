/*
** EPITECH PROJECT, 2019
** activate_animation.c
** File description:
** activate animation
*/

#include "my.h"

int activate_animation(obj_t *obj, sfClock *clock)
{
    if (obj->anim_mode == 1)
        return (84);
    obj->anim_mode = 1;
    reset_time(obj->time_anim, clock);
    return (0);
}

int deactivate_animation(obj_t *obj, sfClock *clock)
{
    if (obj->anim_mode == 0)
        return (84);
    obj->anim_mode = 0;
    reset_time(obj->time_anim, clock);
    return (0);
}
