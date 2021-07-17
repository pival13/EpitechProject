/*
** EPITECH PROJECT, 2019
** my_world.h
** File description:
** header of my_world
*/

#include "rpg.h"

#ifndef MACRO_H
#define MACRO_H

#define MS microseconds
#define SPOS(sprite) (sfSprite_getPosition(sprite))
#define SANG(sprite) (sfSprite_getRotation(sprite))
#define KEY_I() (w->event.type == sfEvtKeyReleased && (w->event.key.co\
de == sfKeySpace || w->event.key.code == sfKeyReturn))
#define KEY_Z() (w->event.type == sfEvtKeyReleased && (w->event.key.co\
de == sfKeyUp || w->event.key.code == sfKeyZ))
#define KEY_Q() (w->event.type == sfEvtKeyReleased && (w->event.key.co\
de == sfKeyLeft || w->event.key.code == sfKeyQ))
#define KEY_S() (w->event.type == sfEvtKeyReleased && (w->event.key.co\
de == sfKeyDown || w->event.key.code == sfKeyS))
#define KEY_D() (w->event.type == sfEvtKeyReleased && (w->event.key.co\
de == sfKeyRight || w->event.key.code == sfKeyD))
#define SIZE(a) (float)sfRenderWindow_getSize(w->win).a
#define TSIZE(text, a) (float)sfTexture_getSize(text).a
#define KEY(letter) (w->event.type == sfEvtKeyPressed && w->event.key.co\
de == letter)
#define KEY_R(letter) (w->event.type == sfEvtKeyReleased && w->event.key.co\
de == letter)
#define TEXT(letter) (w->event.type == sfEvtTextEntered && w->event.text\
.unicode == letter)
#define COLOR(red, green, blue) sfColor_fromRGB(red, green, blue)
#define COLORA(r, g, b, a) sfColor_fromRGBA(r, g, b, a)

#endif
