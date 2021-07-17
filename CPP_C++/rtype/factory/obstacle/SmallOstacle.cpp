/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** SmallOstacle
*/

#include "SmallOstacle.hpp"

SmallOstacle::SmallOstacle()
: Obstacle(nullptr, {456/5, 320/5, 20}, {
    {"Idle", {
        std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../../client/UI/final/img_src/Lobstacle.png",
        Transform({0, 0, 0}, {130, 512, 0}, {0.5, 0.5, 0.5}, {0,0,90}, {0.3,0.3,1}), {130, 0}, 8
    }}
})
{
    _sprite.setColor(sf::Color(200, 255, 200));
}

SmallOstacle::~SmallOstacle()
{
}

Obstacle *createInstance() { return new SmallOstacle(); }