/*
** EPITECH PROJECT, 2018
** change_color
** File description:
** change the color 
*/

#include "csfml.h"
#include <SFML/Graphics.h>

sfColor change_color(sfColor color)
{
    (color.r == 255 && color.g < 255 && color.b == 0) ? color.g++ : color.g;
    (color.r > 0 && color.g == 255 && color.b == 0) ? color.r-- : color.r;
    (color.r == 0 && color.g == 255 && color.b < 255) ? color.b++ : color.b;
    (color.r == 0 && color.g > 0 && color.b == 255) ? color.g-- : color.g;
    (color.r < 255 && color.g == 0 && color.b == 255) ? color.r++ : color.r;
    (color.r == 255 && color.g == 0 && color.b > 0) ? color.b-- : color.b;
    return (color);
}
