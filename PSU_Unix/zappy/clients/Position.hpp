/*
** By Kevin Pruvost, May 2020
** Position.hpp
** File description:
** position
*/

#pragma once

/**
 * @brief Position class on [x, y].
 */
class Position
{
public:
    Position(int xx = 0, int yy = 0);
    ~Position();

    bool operator==(const Position & pos) { return x == pos.x && y == pos.y; }

public:
    int x;
    int y;
};