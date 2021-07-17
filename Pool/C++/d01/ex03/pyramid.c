/*
** EPITECH PROJECT, 2020
** pyramid.c
** File description:
** find the shortest path to the below of the pyramid
*/

#include <stdlib.h>

int pyramid_path2(int size, const int **map, int posx, int posy)
{
    int l1;
    int l2;

    if (posy >= size)
        return 0;
    l1 = map[posy][posx] + pyramid_path2(size, map, posx, posy+1);
    l2 = map[posy][posx] + pyramid_path2(size, map, posx+1, posy+1);
    if (l1 < l2)
        return l1;
    else
        return l2;
}

int pyramid_path(int size, const int **map)
{
    return pyramid_path2(size, map, 0, 0);
}