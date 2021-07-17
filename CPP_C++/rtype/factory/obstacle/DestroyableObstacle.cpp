/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** DestroyableObstacle
*/

#include "DestroyableObstacle.hpp"

DestroyableObstacle::DestroyableObstacle()
: Obstacle(nullptr, {158/2, 160/2, 20}, 1, {
    {"Idle", {
        std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../../client/UI/final/img_src/Mobstacle.png",
        Transform({0, 0, 0}, {158, 160, 0}, {0.5, 0.5, 0.5}, {0,0,90}, {0.5,0.5,1}), {158, 0}, 12
    }}
})
{
}

DestroyableObstacle::~DestroyableObstacle()
{
}

Obstacle *createInstance() { return new DestroyableObstacle(); }