/*
** By Kevin Pruvost, May 2020
** PlayerData.cpp
** File description:
** PlayerData
*/

#include "PlayerData.hpp"

PlayerData::PlayerData()
{
}

PlayerData::~PlayerData()
{
}

std::string PlayerData::orientationToString(PlayerData::Orientation orientation)
{
    if (orientation == PlayerData::Orientation::NORTH)
        return "North";
    if (orientation == PlayerData::Orientation::EAST)
        return "East";
    if (orientation == PlayerData::Orientation::WEST)
        return "West";
    if (orientation == PlayerData::Orientation::SOUTH)
        return "South";
    return "KO";
}