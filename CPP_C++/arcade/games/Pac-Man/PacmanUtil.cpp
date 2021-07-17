/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** Pacman
*/

#include "Pacman.hpp"

void Pacman::tryCrossMap(pos_t &newPos)
{
    if (newPos[0] < getMapWidth() / 2 - mapSize[0]/2)
        newPos[0] = getMapWidth() / 2 + mapSize[0]/2 - 1;
    else if (newPos[0] > getMapWidth() / 2 + mapSize[0]/2 - 1)
        newPos[0] = getMapWidth() / 2 - mapSize[0]/2;
    else if (newPos[1] < getMapHeight() / 2 - mapSize[1]/2)
        newPos[1] = getMapHeight() / 2 + mapSize[1]/2 - 1;
    else if (newPos[1] > getMapHeight() / 2 + mapSize[1]/2 - 1)
        newPos[1] = getMapHeight() / 2 - mapSize[1]/2;
}

bool Pacman::isComplete()
{
    for (size_t i = 0; i < getMapWidth(); i++)
        for (size_t j = 0; j < getMapHeight(); j++)
            if (getMapAt(i, j) == POINT || getMapAt(i, j) == SUPER_POINT)
                return false;
    return true;
}

pos_t Pacman::getPos(char obj)
{
    for (size_t i = 0; i < getMapWidth(); i++)
        for (size_t j = 0; j < getMapHeight(); j++)
            if (getMapAt(i, j) == obj)
                return {i, j};

    char ghosts[] = {GHOST1, GHOST2, GHOST3, GHOST4};
    for (int i = 0; i != 4; i++)
        if (obj == ghosts[i])
            return beginGhost[i];
    return {0,0};
}

void Pacman::refreshMap(char old, char newc)
{
    for (size_t x = 0; x != getMapWidth(); x++)
        for (size_t y = 0; y != getMapHeight(); y++)
            if (getMapAt(x, y) == old)
                setMapAt(x, y, newc);
}

bool Pacman::isEatable(pos_t pos)
{
    const char c = getMapAt(pos);
    return c == POINT || c == SUPER_POINT || c == EAT_GHOST1 || c == EAT_GHOST2 || c == EAT_GHOST3 || c == EAT_GHOST4;
}

bool Pacman::isEnemy(pos_t pos)
{
    const char c = getMapAt(pos);
    return c == GHOST1 || c == GHOST2 || c == GHOST3 || c == GHOST4;
}

bool Pacman::isWalkableGhost(pos_t pos)
{
    const char c = getMapAt(pos);

    if (pos[0] == (size_t)-1 || pos[1] == (size_t)-1 || pos[0] >= getMapWidth() || pos[1] >= getMapHeight())
        return false;
    if (isEnemy(pos) || c == WALL || c == EAT_GHOST1 || c == EAT_GHOST2 || c == EAT_GHOST3 || c == EAT_GHOST4)
        return false;
    if (superTimer >= now - msec(10000))
        return c != PLAYER;
    else
        return true;
}