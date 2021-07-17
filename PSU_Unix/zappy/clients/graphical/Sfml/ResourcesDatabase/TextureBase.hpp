/*
** EPITECH PROJECT, 2020
** TextureBase.hpp
** File description:
** texture base
*/

#pragma once

// Project includes
#include "SfmlIncludes.hpp"

/**
 * @brief Texture Database.
 */
class TextureBase
{
public:
    TextureBase();
    ~TextureBase();

public:
    /**
     * @brief Gets a texture with an index corresponding to the Constants::TextureId enumeration.
     * @param textureId
     * @return sf::Texture&
     */
    sf::Texture & getTexture(Constants::TextureId textureId);
    /**
     * @brief Same as getTexture().
     * @param tId
     * @return sf::Texture&
     */
    sf::Texture & operator[](Constants::TextureId tId);

private:
    KVector<sf::Texture> _textures;
};

extern TextureBase textureBase;