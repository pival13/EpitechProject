/*
** EPITECH PROJECT, 2020
** SfmlTools.cpp
** File description:
** sfml
*/

#include "SfmlTools.hpp"

sf::Clock globalClock;

std::unique_ptr<sf::Texture> newTexture(const std::string & name)
{
    std::unique_ptr<sf::Texture> newPtr(new sf::Texture);

    newPtr->loadFromFile(name);
    return newPtr;
}

std::unique_ptr<sf::Sprite> newSprite(const sf::Texture & texture)
{
    std::unique_ptr<sf::Sprite> newPtr(new sf::Sprite);

    newPtr->setTexture(texture);
    return newPtr;
}

std::unique_ptr<sf::Sprite> newSprite(const std::string & name)
{
    std::unique_ptr<sf::Sprite> newPtr(new sf::Sprite);
    sf::Texture texture;

    texture.loadFromFile(name);
    newPtr->setTexture(texture);
    return newPtr;
}

std::unique_ptr<sf::Font> newFont(const std::string & path)
{
    std::unique_ptr<sf::Font> newPtr(new sf::Font);

    newPtr->loadFromFile(path);
    return newPtr;
}

void resetTime(sf::Time & time)
{
    time = globalClock.getElapsedTime();
}

sf::Int32 getMs(sf::Time & time)
{
    const auto ms = globalClock.getElapsedTime().asMilliseconds() -
                    time.asMilliseconds();
    return ms;
}

sf::Color degradeColor(sf::Color color)
{
    color.g += 50;
    color.r += 50;
    color.b += 50;

    (color.g > 255) ? color.g = 55 : 0;
    (color.b > 255) ? color.b = 55 : 0;
    (color.r > 255) ? color.r = 55 : 0;
    
    return (color);
}