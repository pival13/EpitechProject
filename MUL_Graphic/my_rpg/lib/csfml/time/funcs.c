/*
** EPITECH PROJECT, 2019
** funcs.c
** File description:
** funcs for time managing
*/

#include "my.h"
#include "struct.h"

time_obj *create_time_obj(sfClock *clock)
{
    time_obj *time = malloc(sizeof(struct time_obj));

    time->time = sfClock_getElapsedTime(clock);
    time->seconds_init = time->time.microseconds / 1000000.0;
    time->seconds = 0;
    return (time);
}

void destroy_time_obj(time_obj *time)
{
    free(time);
}

void reset_time(time_obj *time, sfClock *clock)
{
    time->time = sfClock_getElapsedTime(clock);
    time->seconds_init = time->time.microseconds / 1000000.0;
    time->seconds = 0.0;
}

void end_pause_time(time_obj *time, sfClock *clock)
{
    time->time = sfClock_getElapsedTime(clock);
    time->seconds_init = time->time.microseconds / 1000000.0;
}

float get_time(time_obj *time, sfClock *clock)
{
    time->time = sfClock_getElapsedTime(clock);
    time->seconds += (time->time.microseconds / 1000000.0) - time->seconds_init;
    time->seconds_init = time->time.microseconds / 1000000.0;
    return (time->seconds);
}
