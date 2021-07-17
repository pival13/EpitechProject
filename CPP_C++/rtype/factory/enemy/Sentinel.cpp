/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Sentinel
*/

#include "Sentinel.hpp"

Sentinel::Sentinel()
: Enemy(nullptr, EnemyType::EnemySentinel, {200*0.3, 200*0.3, 200}, 1, {
    {"Idle", {
        std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../../client/UI/final/img_src/PE.png",
        Transform({0, 0, 0}, {206, 205, 0}, {0.5, 0.5, 0.5}, {0,0,0}, {0.3, 0.3, 1}), {206, 0}, 21
    }}
})
{
    playAnimation("Idle", true);
}

Sentinel::~Sentinel()
{
}

Enemy *createInstance() { return new Sentinel(); }