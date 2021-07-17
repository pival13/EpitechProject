/*
** EPITECH PROJECT, 2020
** TextureBase.hpp
** File description:
** texture base
*/

#pragma once

// Project includes
#include "SfmlTools.hpp"

// C++ includes
#include <vector>
#include <memory>

class TextureBase
{
public:
    TextureBase();
    ~TextureBase();

public:
    sf::Texture & getTexture(Jam::TextureId textureId);
    sf::Texture & operator[](Jam::TextureId tId);

private:
    std::vector<std::unique_ptr<sf::Texture>> _textures;
};

extern TextureBase textureBase;

class FontBase
{
public:
    FontBase();
    ~FontBase();

public:
    sf::Font & getFont(Jam::FontId textureId);
    sf::Font & operator[](Jam::FontId tId);

private:
    std::vector<std::unique_ptr<sf::Font>> _fonts;
};

extern FontBase fontBase;