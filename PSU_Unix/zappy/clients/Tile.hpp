/*
** By Kevin Pruvost, May 2020
** Tile.hpp
** File description:
** tile
*/

#pragma once

// Project includes
#include "Position.hpp"
#include "InventoryData.hpp"

// C++ includes
#include <cstddef>

/**
 * @brief Contains a tile's datas.
 */
class Tile
{
public:
    Tile(const Position & pos = {0, 0}, size_t f = 0, size_t l = 0, size_t d = 0, size_t s = 0, size_t m = 0, size_t p = 0, size_t t = 0);
    ~Tile();

public:
    Position pos = {0, 0};
    InventoryData inventory;
};