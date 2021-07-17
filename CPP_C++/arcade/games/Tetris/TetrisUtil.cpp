/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** TetrisUtil
*/

#include "Tetris.hpp"

bool Tetris::isActivePiece(char c) const
{
    return (c == 'i' || c == 'o' || c == 't' || c == 'j' || c == 'l' || c == 'z' || c == 's');
}

bool Tetris::isBlockPiece(char c) const
{
    return (c == 'I' || c == 'O' || c == 'T' || c == 'J' || c == 'L' || c == 'Z' || c == 'S');
}

bool Tetris::isActivePiece(pos_t pos) const { return isActivePiece(getMapAt(pos)); }
bool Tetris::isBlockPiece(pos_t pos) const { return isBlockPiece(getMapAt(pos)); }

bool Tetris::canMove(spos_t dir) const
{
    for (size_t x = 0; x != getMapWidth(); x++)
        for (size_t y = 0; y != getMapHeight(); y++)
            if (isActivePiece({x,y}) && (x+dir[0] < getMapWidth()/2-5 || y+dir[1] < getMapHeight()/2-11 || 
                                         x+dir[0] >= getMapWidth()/2+5 || y+dir[1] >= getMapHeight()/2+11 || 
                                         isBlockPiece({x+dir[0], y+dir[1]})))
                return false;
    return true;
}

std::array<size_t, 4> Tetris::getRect(std::vector<pos_t> poss) const
{
    size_t minx = getMapWidth(),
           miny = getMapHeight(),
           maxx = 0,
           maxy = 0;

    for (pos_t pos : poss) {
        if (pos[0] < minx)
            minx = pos[0];
        if (pos[1] < miny)
            miny = pos[1];
        if (pos[0] > maxx)
            maxx = pos[0];
        if (pos[1] > maxy)
            maxy = pos[1];
    }
    return {minx, miny, maxx-minx+1, maxy-miny+1};
}