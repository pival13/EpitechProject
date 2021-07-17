/*
** By Kevin Pruvost, May 2020
** Tile.cpp
** File description:
** Tile.hpp
*/

#include "Tile.hpp"

Tile::Tile(const Position & ppos, size_t f, size_t l, size_t d, size_t s, size_t m, size_t p, size_t t)
    : pos { ppos }
    , inventory(f, l, d, s, m, p, t)
{
}

Tile::~Tile()
{
}