/*
** EPITECH PROJECT, 2019
** animation_prog_scale.c
** File description:
** animation prog scale
*/

#include "my.h"

void animation_prog_scale(obj_t *obj, sfClock *clock, float sc, float speed)
{
    if (obj->anim_mode == 1) {
        mod_scale_p(obj, get_time(obj->time_anim, clock) / speed);
        if (obj->scale.x > sc)
            mod_scale(obj, sc);
    } else {
        mod_scale_p(obj, get_time(obj->time_anim, clock) / (-speed));
        if (obj->scale.x < 1)
            mod_scale(obj, 1);
    }
}
