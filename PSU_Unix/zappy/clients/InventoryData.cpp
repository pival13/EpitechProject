/*
** By Kevin Pruvost, May 2020
** InventoryData.cpp
** File description:
** in
*/

#include "InventoryData.hpp"

InventoryData::InventoryData(size_t f, size_t l, size_t d, size_t s, size_t m, size_t p, size_t t)
    : food { f }
    , linemate { l }
    , deraumere { d }
    , sibur { s }
    , mendiane { m }
    , phiras { p }
    , thystmane { t }
{
}

InventoryData::~InventoryData()
{
}