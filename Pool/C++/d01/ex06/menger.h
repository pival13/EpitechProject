/*
** EPITECH PROJECT, 2020
** menger.h
** File description:
** header of menger
*/

#ifndef MENGER_H
#define MENGER_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void menger_face(char *filename, size_t len, int recur);
void menger(int len, int recur[2], int init_pos[2], unsigned int **img);

#endif