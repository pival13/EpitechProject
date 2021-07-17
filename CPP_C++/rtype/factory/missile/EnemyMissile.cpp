/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** EnemyMissile
*/

#include "EnemyMissile.hpp"

EnemyMissile::EnemyMissile()
: Missile(nullptr, MissileType::MissileEnemy, {20,20,20}, 
    std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../../client/UI/final/img_src/erocket.png", {20, 20}, {1, 1})//TODO)
{
}

EnemyMissile::~EnemyMissile()
{
}

Missile *createInstance() { return new EnemyMissile(); }