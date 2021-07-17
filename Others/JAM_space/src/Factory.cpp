/*
** EPITECH PROJECT, 2020
** JAM_space_2019
** File description:
** Factory
*/

#include "Factory.hpp"

using namespace Jam;

std::unique_ptr<AEatable> Factory::createPlanet()
{
    return std::unique_ptr<AEatable>(new Eatable(textureBase[TextureId::PLANET]));
}

std::unique_ptr<AEatable> Factory::createSpaceship()
{
    return std::unique_ptr<AEatable>(new Eatable(textureBase[TextureId::SPACESHIP]));
}

std::unique_ptr<AEatable> Factory::createBoss()
{
    return std::unique_ptr<AEatable>(new Eatable(textureBase[TextureId::BOSS]));
}

std::unique_ptr<AEatable> Factory::createStar()
{
    return std::unique_ptr<AEatable>(new Eatable(textureBase[TextureId::STAR]));
}

std::unique_ptr<AEatable> Factory::createComet()
{
    return std::unique_ptr<AEatable>(new Eatable(textureBase[TextureId::COMET]));
}

std::unique_ptr<AEatable> Factory::createSatellite()
{
    return std::unique_ptr<AEatable>(new Eatable(textureBase[TextureId::SATELLITE]));
}

std::unique_ptr<AEatable> Factory::createEatable()
{
    unsigned int create = rand() % 6;

    switch (create)
    {
        case PLANET:
            return createPlanet();
            break;
        case SPACESHIP:
            return createSpaceship();
            break;
        case STAR:
            return createStar();
            break;
        case COMET:
            return createComet();
            break;
        case SATELLITE:
            return createSatellite();
        default:
            return createPlanet();
            break;
    }
}
