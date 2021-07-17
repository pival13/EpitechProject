/*
** EPITECH PROJECT, 2020
** TextureBase.cpp
** File description:
** texture
*/

#include "TextureBase.hpp"

using namespace Jam;

TextureBase textureBase;
FontBase fontBase;

TextureBase::TextureBase()
{
    // Init Textures
    for (const auto path : Constants::backgroundPaths)
        _textures.push_back(newTexture(path));
}

TextureBase::~TextureBase()
{
}

sf::Texture & TextureBase::getTexture(Jam::TextureId textId)
{
    return *_textures[textId];
}

sf::Texture & TextureBase::operator[](Jam::TextureId tId)
{
    return getTexture(tId);
}

FontBase::FontBase()
{
    // Init Textures
    for (const auto path : Constants::fontPaths)
        _fonts.push_back(newFont(path));
}

FontBase::~FontBase()
{
}

sf::Font & FontBase::getFont(Jam::FontId textId)
{
    return *_fonts[textId];
}

sf::Font & FontBase::operator[](Jam::FontId tId)
{
    return getFont(tId);
}