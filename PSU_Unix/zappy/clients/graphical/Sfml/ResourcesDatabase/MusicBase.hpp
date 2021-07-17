/*
** By Kevin Pruvost, May 2020
** File description:
** MusicBase class.
*/

#pragma once

// Project includes
#include "SfmlIncludes.hpp"

// C++ includes
#include <memory>

/**
 * @brief Music Database.
 */
class MusicBase
{
public:
    MusicBase();
    ~MusicBase();

public:
    /**
     * @brief Gets a music with an index corresponding to the Constants::MusicId enumeration.
     * @param textureId
     * @return sf::Music &
     */
    sf::Music & getMusic(Constants::MusicId textureId);
    /**
     * @brief Same as getMusic().
     * @param tId
     * @return sf::Music&
     */
    sf::Music & operator[](Constants::MusicId tId);

private:
    KVector<std::unique_ptr<sf::Music>> _musics;
};

extern MusicBase musicBase;