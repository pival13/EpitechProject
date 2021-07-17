/*
** By Kevin Pruvost, May 2020
** File description:
** MusicBase class.
*/

#include "MusicBase.hpp"

MusicBase musicBase;

MusicBase::MusicBase()
{
    // Init Textures
    for (const auto & path : Constants::musicsPaths)
    {
        auto ptr = std::make_unique<sf::Music>();
        ptr->openFromFile(Constants::musicsPath + path);
        ptr->setVolume(35);
        _musics.push_back(std::move(ptr));
    }
}

MusicBase::~MusicBase()
{
}

sf::Music & MusicBase::getMusic(Constants::MusicId textId)
{
    return *_musics[textId];
}

sf::Music & MusicBase::operator[](Constants::MusicId tId)
{
    return getMusic(tId);
}