/*
** By Kevin Pruvost, May 2020
** EggData.hpp
** File description:
** EggData
*/

#pragma once

#include "PlayerData.hpp"

/**
 * @brief Class containing an egg's datas.
 */
class EggData : virtual public PlayerData
{
public:
    EggData();
    ~EggData();

public:
    bool isHatching = false;
    int laidBy = 0;
};