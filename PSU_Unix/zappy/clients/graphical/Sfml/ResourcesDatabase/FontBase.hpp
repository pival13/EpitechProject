/*
** By Kevin Pruvost, May 2020
** File description:
** FontBase class.
*/

#pragma once

// Project includes
#include "SfmlIncludes.hpp"

/**
 * @brief Fonts Database.
 */
class FontBase
{
public:
    FontBase();
    ~FontBase();

public:
    /**
     * @brief Gets a font according to the index parameter.
     * @param textureId
     * @return sf::Font&
     */
    sf::Font & getFont(Constants::FontId textureId);
    sf::Font & operator[](Constants::FontId tId);

private:
    KVector<sf::Font> _fonts;
};

extern FontBase fontBase;