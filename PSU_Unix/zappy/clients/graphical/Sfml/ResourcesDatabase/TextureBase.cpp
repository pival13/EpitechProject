/*
** EPITECH PROJECT, 2020
** TextureBase.cpp
** File description:
** texture
*/

#include "TextureBase.hpp"

TextureBase textureBase;

TextureBase::TextureBase()
{
    // Init Textures
    for (const auto & path : Constants::spritesPaths)
    {
        _textures.emplace_back();
        _textures.back().loadFromFile(Constants::spritesPath + std::get<0>(path));
    }
}

TextureBase::~TextureBase()
{
}

sf::Texture & TextureBase::getTexture(Constants::TextureId textId)
{
    return _textures[textId];
}

sf::Texture & TextureBase::operator[](Constants::TextureId tId)
{
    return getTexture(tId);
}