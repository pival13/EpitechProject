/*
** By Kevin Pruvost, May 2020
** InventoryData.hpp
** File description:
** inven
*/

#pragma once

// Project includes
#include "Exception.hpp"

// C++ includes
#include <cstddef>

/**
 * @brief Class containting an inventory's datas.
 */
class InventoryData
{
public:
    InventoryData(size_t f = 0, size_t l = 0, size_t d = 0, size_t s = 0, size_t m = 0, size_t p = 0, size_t t = 0);
    ~InventoryData();

    /**
     * @brief Operator browsing the inventory with an index corresponding to the
     * InventoryDataEnum.
     * @param i
     * @return size_t
     */
    size_t operator[](size_t i) const
    {
        if (i == InventoryDataEnum::FOOD)
            return food;
        if (i == InventoryDataEnum::LINEMATE)
            return linemate;
        if (i == InventoryDataEnum::DERAUMERE)
            return deraumere;
        if (i == InventoryDataEnum::SIBUR)
            return sibur;
        if (i == InventoryDataEnum::MENDIANE)
            return mendiane;
        if (i == InventoryDataEnum::PHIRAS)
            return phiras;
        if (i == InventoryDataEnum::THYSTMANE)
            return thystmane;
        return 0;
    }

    size_t & operator[](size_t i)
    {
        if (i == InventoryDataEnum::FOOD)
            return food;
        if (i == InventoryDataEnum::LINEMATE)
            return linemate;
        if (i == InventoryDataEnum::DERAUMERE)
            return deraumere;
        if (i == InventoryDataEnum::SIBUR)
            return sibur;
        if (i == InventoryDataEnum::MENDIANE)
            return mendiane;
        if (i == InventoryDataEnum::PHIRAS)
            return phiras;
        if (i == InventoryDataEnum::THYSTMANE)
            return thystmane;
        throw EXCEPTION("Wrong Inventory index.");
    }

public:
    /**
     * @brief Enum used for browsing the inventory's datas.
     */
    enum InventoryDataEnum
    {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTMANE
    };
    size_t food = 0;
    size_t linemate = 0;
    size_t deraumere = 0;
    size_t sibur = 0;
    size_t mendiane = 0;
    size_t phiras = 0;
    size_t thystmane = 0;
};