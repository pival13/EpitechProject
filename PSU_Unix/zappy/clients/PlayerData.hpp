/*
** By Kevin Pruvost, May 2020
** PlayerData.hpp
** File description:
** PlayerData
*/

#pragma once

// C++ includes
#include <string>

// Project includes
#include "Position.hpp"
#include "InventoryData.hpp"

/**
 * @brief Contains player datas.
 */
class PlayerData
{
public:
    enum Orientation
    {
        NORTH = 1,
        EAST,
        SOUTH,
        WEST
    };

public:
    PlayerData();
    ~PlayerData();

    /**
     * @brief Returns a string of the orientation given.
     * @param orientation
     * @return std::string
     */
    static std::string orientationToString(Orientation orientation);

public:
    Position position = {0, 0};
    int level = 0;
    Orientation orientation = Orientation::NORTH;
    InventoryData inventory;
    int id = 0;
    std::string teamName;
    bool isIncanting = false;
    int isIncantingToLvl = 0;
    bool dead = false;
    bool isLayingEgg = false;
};