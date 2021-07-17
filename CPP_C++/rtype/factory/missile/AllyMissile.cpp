/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** AllyMissile
*/

#include "AllyMissile.hpp"

AllyMissile::AllyMissile()
: Missile(nullptr, MissileType::MissileAlly, {20,20,20}, 
    std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../../client/UI/final/img_src/procket.png", {20, 20}, {1, 1}, 0, {1, 1})//TODO
{
}

AllyMissile::~AllyMissile()
{
}

Missile *createInstance() { return new AllyMissile(); }