/*
** EPITECH PROJECT, 2020
** JAM_space_2019
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include <memory>
#include "Eatable.hpp"
#include "TextureBase.hpp"

class Jam::Factory
{
public:
    enum EatableList
    {
        PLANET = 0,
        SPACESHIP = 1,
        BOSS = 2,
        STAR = 3,
        COMET = 4,
        SATELLITE = 5
    };

    static std::unique_ptr<AEatable> createEatable();
    static std::unique_ptr<AEatable> createBoss();

private:
    static std::unique_ptr<AEatable> createPlanet();
    static std::unique_ptr<AEatable> createSpaceship();
    static std::unique_ptr<AEatable> createStar();
    static std::unique_ptr<AEatable> createComet();
    static std::unique_ptr<AEatable> createSatellite();
};

#endif /* !FACTORY_HPP_ */
