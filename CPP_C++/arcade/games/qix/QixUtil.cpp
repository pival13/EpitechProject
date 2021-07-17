/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** Qix
*/

#include "Qix.hpp"

bool Qix::isComplete()
{
    size_t nb = 0;

    for (size_t x = 0; x != getMapWidth(); x++)
        for (size_t y = 0; y != getMapHeight(); y++)
            if (getMapAt(x, y) == GROUND)
                nb++;
    if (nb <= pow(std::min(getMapWidth(), getMapHeight()), 2) * (1-(0.6+0.05*(level < 8 ? level : 7))))
        return true;
    return false;
}

bool Qix::isNextCell(size_t x, size_t y, char cell, bool large) const
{
    auto pos = posNextCell(x, y, cell, large);
    return pos[0] != 0 || pos[1] != 0;
}

pos_t Qix::posCloserBorder(size_t x, size_t y) const
{
    return {x, y};
}

pos_t Qix::posNextCell(size_t x, size_t y, char cell, bool large) const
{
    if (x != 0) {
        if (large && y != 0 && getMapAt(x-1, y-1) == cell)
            return {x-1, y-1};
        else if (large && y != getMapHeight()-1 && getMapAt(x-1, y+1) == cell)
            return {x-1, y+1};
        else if (getMapAt(x-1, y) == cell)
            return {x-1, y};
    }
    if (x != getMapWidth()-1) {
        if (large && y != 0 && getMapAt(x+1, y-1) == cell)
            return {x+1, y-1};
        else if (large && y != getMapHeight()-1 && getMapAt(x+1, y+1) == cell)
            return {x+1, y+1};
        else if (getMapAt(x+1, y) == cell)
            return {x+1, y};
    }
    if (y != 0 && getMapAt(x, y-1) == cell)
        return {x, y-1};
    else if (y != getMapHeight()-1 && getMapAt(x, y+1) == cell)
        return {x, y+1};
    return {0, 0};
}

void Qix::refreshMap(char old, char newc)
{
    for (size_t x = 0; x != getMapWidth(); x++)
        for (size_t y = 0; y != getMapHeight(); y++)
            if (getMapAt(x, y) == old)
                setMapAt(x, y, newc);
}

bool Qix::isNotWithQix(size_t x, size_t y)
{
    if (getMapAt(x, y) != 0 && getMapAt(x, y) != 1) {
        refreshMap(1, 0); return false; }

    if (x != 0 && getMapAt(x-1, y) == 0) {
        setMapAt(x-1, y, 1);
        if (!isNotWithQix(x-1, y))
            return false;
    } else if (x != 0 && getMapAt(x-1, y) == QIX) {
        refreshMap(1, 0); return false; }

    if (x != getMapWidth()-1 && getMapAt(x+1, y) == 0) {
        setMapAt(x+1, y, 1);
        if (!isNotWithQix(x+1, y))
            return false;
    } else if (x != getMapWidth()-1 && getMapAt(x+1, y) == QIX) {
        refreshMap(1, 0); return false; }

    if (y != 0 && getMapAt(x, y-1) == 0) {
        setMapAt(x, y-1, 1);
        if (!isNotWithQix(x, y-1))
            return false;
    } else if (y != 0 && getMapAt(x, y-1) == QIX) {
        refreshMap(1, 0); return false; }

    if (y != getMapHeight()-1 && getMapAt(x, y+1) == 0) {
        setMapAt(x, y+1, 1);
        if (!isNotWithQix(x, y+1))
            return false;
    } else if (y != getMapHeight()-1 && getMapAt(x, y+1) == QIX) {
        refreshMap(1, 0); return false; }

    return true;
}

pos_t Qix::getQixPos() const
{
    for (size_t i = 0; i < getMapWidth(); i++)
        for (size_t j = 0; j < getMapHeight(); j++)
            if (getMapAt(i, j) == PLAYER || getMapAt(i, j) == PLAYER_WALK)
                return {i, j};
    return {0, 0};
}

std::array<pos_t, 3> Qix::getEnemyPos() const
{
    std::array<pos_t, 3> arr({pos_t({0,0}), pos_t({0,0}), pos_t({0,0})});

    for (size_t i = 0; i < getMapWidth(); i++)
        for (size_t j = 0; j < getMapHeight(); j++)
            if (getMapAt(i, j) == QIX) {
                arr[0][0] = i; arr[0][1] = j; }
            else if (getMapAt(i, j) == STARK && arr[1][0] == 0 && arr[1][1] == 0) {
                arr[1][0] = i; arr[1][1] = j; }
            else if (getMapAt(i, j) == STARK) {
                arr[2][0] = i; arr[2][1] = j; }
    return arr;
}

bool Qix::isWalkable(size_t x, size_t y, char obj)
{
    if (x == size_t(-1) || y == size_t(-1) || x == getMapWidth() || y == getMapHeight())
        return false;

    if (obj == QIX)
        return (getMapAt(x, y) == GROUND || getMapAt(x, y) == PLAYER_WALK || getMapAt(x, y) == TRAIL || getMapAt(x, y) == BURN);
    else if (obj == STARK)
        return (getMapAt(x, y) == BORDER || getMapAt(x, y) == PLAYER);
    else if (obj == PLAYER || obj == PLAYER_WALK)
        return (getMapAt(x, y) == GROUND || getMapAt(x, y) == BORDER || getMapAt(x, y) == QIX || getMapAt(x, y) == STARK_TAIL || getMapAt(x, y) == STARK);
    else
        return false;
}