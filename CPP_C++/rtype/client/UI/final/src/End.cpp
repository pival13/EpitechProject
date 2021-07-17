/*
** EPITECH PROJECT, 2020
** RType_2020
** File description:
** End
*/

#include "End.hpp"

End::End()
: AScene(END)
{
    std::string dir = __FILE__;
    dir = dir.substr(0, dir.find_last_of("\\/"));
    sf::Texture *textureBg = new sf::Texture();

    if (textureBg->loadFromFile(dir + "/../img_src/end.png") == false) exit(EXIT_FAILURE);
    _bg = sf::Sprite(*textureBg);
    _bg.setPosition(0, 0);
}

End::~End()
{
}

void End::getEvents(game_t *, sf::RenderWindow *)
{
}

void End::updateGame(game_t *gm, sf::RenderWindow *window)
{
    _time = gm->clock.getElapsedTime();
    if (_time.asSeconds() > 4.0f)
        window->close();
}

void End::drawGame(game_t *, sf::RenderWindow *window)
{
    window->clear();
    window->draw(_bg);
}
