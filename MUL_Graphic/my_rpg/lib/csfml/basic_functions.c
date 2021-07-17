/*
** EPITECH PROJECT, 2018
** basic_functions.c
** File description:
** first csfml funcs
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/my.h"

float clock_getseconds(sfClock *clock)
{
    sfTime time = sfClock_getElapsedTime(clock);
    float seconds = time.microseconds / 1000000.0;

    return (seconds);
}
