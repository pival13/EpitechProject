/*
** EPITECH PROJECT, 2020
** menger
** File description:
** the menger sponge
*/

#include "menger.h"

void menger(int len, int recur, int pos[2])
{
    int nb = 0;

    if (recur > 0) {
        nb = len/3;
        printf("%u%u%u ", (int)(nb/100), (int)(nb/10%10), (int)(nb%10));
        nb = pos[0]+len/3;
        printf("%u%u%u ", (int)(nb/100), (int)(nb/10%10), (int)(nb%10));
        nb = pos[1]+len/3;
        printf("%u%u%u\n", (int)(nb/100), (int)(nb/10%10), (int)(nb%10));
        menger(len/3, recur-1, (int[2]){pos[0], pos[1]});
        menger(len/3, recur-1, (int[2]){pos[0], pos[1]+len/3});
        menger(len/3, recur-1, (int[2]){pos[0], pos[1]+len/3*2});
        menger(len/3, recur-1, (int[2]){pos[0]+len/3, pos[1]});
        menger(len/3, recur-1, (int[2]){pos[0]+len/3, pos[1]+len/3*2});
        menger(len/3, recur-1, (int[2]){pos[0]+len/3*2, pos[1]});
        menger(len/3, recur-1, (int[2]){pos[0]+len/3*2, pos[1]+len/3});
        menger(len/3, recur-1, (int[2]){pos[0]+len/3*2, pos[1]+len/3*2});
    }
}