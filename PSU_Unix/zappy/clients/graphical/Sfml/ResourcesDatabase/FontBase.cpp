/*
** By Kevin Pruvost, May 2020
** File description:
** FontBase class.
*/

#include "FontBase.hpp"

FontBase fontBase;

FontBase::FontBase()
{
    // Init Textures
    for (const auto & path : Constants::fontsPaths)
    {
        _fonts.emplace_back();
        _fonts.back().loadFromFile(Constants::fontsPath + path);
    }
}

FontBase::~FontBase()
{
}

sf::Font & FontBase::getFont(Constants::FontId textId)
{
    return _fonts[textId];
}

sf::Font & FontBase::operator[](Constants::FontId tId)
{
    return getFont(tId);
}