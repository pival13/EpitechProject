/*
** EPITECH PROJECT, 2020
** SfmlTools.hpp
** File description:
** sfml
*/

#pragma once

// Project includes
#include "Sfml.hpp"
#include "Jam.hpp"
#include "TextureBase.hpp"

std::unique_ptr<sf::Texture> newTexture(const std::string & name);
std::unique_ptr<sf::Sprite>  newSprite(const sf::Texture & texture);
std::unique_ptr<sf::Sprite>  newSprite(const std::string & name);

std::unique_ptr<sf::Font> newFont(const std::string & path);

extern sf::Clock globalClock;

sf::Int32 getMs(sf::Time & time);
void resetTime(sf::Time & time);

sf::Color degradeColor(sf::Color color);